/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file process/searcher.cpp
 * @author caolin01(com@baidu.com)
 * @date 2014/06/12 21:20:07
 * @brief 
 *  
 **/
#include "searcher.h"
#include "rank.h"
#include "util.h"
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::map;
using std::ios;

using std::ifstream;
#define DEBUG
namespace cute_engine{

Searcher::Searcher():_pword_segment(NULL),_pword_dict(NULL){

}
Searcher::Searcher(Segment *in_segment,WordDict *in_word_dict):_pword_segment(in_segment),_pword_dict(in_word_dict){

}
Searcher::~Searcher(){
    if(NULL != _pword_segment){
//        delete _pword_segment;
        _pword_segment = NULL;
    }

    if(NULL != _pword_dict){
//        delete _pword_dict;
        _pword_dict = NULL;
    }
}
/*
void Searcher::init(char *dict_path){
    if(NULL == _pword_segment){
        _pword_segment = new Segment();
        _pword_segment->init(dict_path,1024);
    }
    if(NULL == _pword_dict){
        _pword_dict = new WordDict();
    }
}*/

void Searcher::test_search(char* path){

    FILE * file = fopen(path,"r");
    if(NULL == file){
        cerr<<"open raw file to search error"<<endl; 
        return;
    } 
    while(!feof(file)){
        char buffer[1024];
        fgets(buffer,1024,file);
        string doc_line(buffer);
        vector<string> doc_info_vec;
        explode(doc_line,"\t",doc_info_vec);
/*
        if(doc_info_vec.size()!=4){
            continue;
        } */
        parse_query(doc_info_vec[0]);
        get_result();
    }
}
void Searcher::set_average_length(int len){
    _average_length = len;
}
void Searcher::set_inverted_index(std::map<size_t,WordItem > &inmap){
    _inverted_index = inmap;
}
void Searcher::set_inverted_posting_list(std::vector<InvertedPosting> &invec){
    _inverted_posting_list = invec;
}
void Searcher::set_hit_list(std::vector<Hit> &invec){
    _hit_list = invec;
}

void Searcher::set_docs_info(std::map<int,DocumentInfo> &inmap){
    _docs_info = inmap;
}

void Searcher::set_total_doc_num(int num){
    _total_docs_num  = num;
}

void Searcher::parse_query(string query_str){
#ifdef DEBUG
    cout<<"query_str:"<<query_str<<endl;
#endif
    vector<token_t> token_vec;
    _pword_segment->segment_string(const_cast<char*>(query_str.c_str()),token_vec);
    int count = token_vec.size();
    vector<Collector> collector_vec;
    if( count > 0 ){
        //º∆À„≤È—Øquery=£>tf
        map<string,int> token_tf;
        for(int i=0;i<count; i++){
            string token = token_vec[i].buffer;
            map<string,int>::iterator iter = token_tf.find(token);
            if(iter != token_tf.end()){
                ++ iter->second; 
            }else{
                token_tf.insert(std::pair<string,int>(token,1)); 
            }
        }

        map<size_t,int> token_id_tf;
        map<string,int>::iterator token_tf_iter = token_tf.begin();
        while(token_tf_iter != token_tf.end() ){
            string token = token_tf_iter->first;
            DictInfo info = _pword_dict->get_word_info(token);
            if(info.dict_id != -1){
                size_t token_id = info.dict_id;
                #ifdef DEBUG
                    cout<<"token:"<<token<<" token_id:"<<token_id;
                #endif

                //≥ı ºªØ¥Ê¥¢≤È—Ø¥ °¢∂‘”¶µπ≈≈µ»œ‡πÿ–≈œ¢
                map<size_t,WordItem>::iterator  inverted_index_iter = _inverted_index.find(token_id);
                if(inverted_index_iter != _inverted_index.end() ){
                    int post_begin = (inverted_index_iter->second).begin;
                    int post_end = (inverted_index_iter->second).end;

                    Collector collector;
                    collector._word_id = token_id;
                    collector._tf = token_tf_iter->second;
                    double tmp_num = (double)(_total_docs_num + 0.5);
                    collector._idf = log(tmp_num / ((double)(info.df + 0.5)) );
                    collector._iter = _inverted_posting_list.begin() + post_begin;
                    collector._iter_end = _inverted_posting_list.begin() + post_end;
                    collector._doc_id = (collector._iter)->doc_id;
                    collector._hit_iter = _hit_list.begin();
                    collector._average_length = _average_length;
                    collector._docs_info = &_docs_info;
                    collector_vec.push_back(collector);
                    #ifdef DEBUG
                        cout<<" tf:"<<collector._tf<<" idf:"<<collector._idf;
                        cout<<" doc_id:"<<collector._doc_id<<endl;
                    #endif
                }
            }
            ++ token_tf_iter;
            
        }
        init_rank(collector_vec);

    }

}


void Searcher::init_rank(vector<Collector> &vec){
    _prank = new SimRank(vec);
    _prank->rank_docs();
}

void Searcher::get_result(){
    vector<DocScore> docs_score = _prank->get_docs_score();
    //∞¥¥Ú∑÷÷µ¥”¥ÛµΩ–°≈≈–Ú
    sort_heap(docs_score.begin(),docs_score.end(),Rank::score_sort);
    vector<DocScore>::iterator iter = docs_score.begin();
    int line=1;
    while(iter != docs_score.end()){
        size_t doc_id = iter->doc_id;
        double score = iter->doc_score;
        std::map<int,DocumentInfo>::iterator docs_info_iter = _docs_info.find(doc_id);
        if(docs_info_iter != _docs_info.end()){
            cout<<"Ω·π˚"<<line<<" doc_id:"<<doc_id<<" label:"<<(docs_info_iter->second).label<<" score:"<<score<<" title:"<<(docs_info_iter->second).title<<endl;
            line++;    
        }else{
            cout<<"Œ¥’“µΩ∂‘”¶Œƒµµ doc_id"<<doc_id<<endl;
        }
        ++ iter;
    }
}

void Searcher::load_dict(char *path){
    _pword_dict->load_dict(path);
}
void Searcher::load_data(char *path){
    string str_path = string(path);
    string dict_path = str_path + "dict.txt";
    string doc_path = str_path + "docindex.txt";
    load_dict(const_cast<char*>(dict_path.c_str()));
    load_document_index(const_cast<char*>(doc_path.c_str()));
    load_inverted_index(path);
}
void Searcher::load_inverted_index(char* path){
    //∂¡»Îhits¡–±Ì
    string str_path = string(path);
    string hit_path = str_path + "hits";
    ifstream ifs(const_cast<char*>(hit_path.c_str()),std::ifstream::in);
    if(NULL == ifs){
        cerr<<"open file to read hits error"<<endl; 
        return;
    } 
    string str_in;
    while(!ifs.eof()){
        getline(ifs,str_in); 
        vector<string> vec;
        explode(str_in,"#",vec);
        int nsize=vec.size();
        for(int i=0;i<nsize;i++){
            Hit hit;
            hit.pos = string_to_num<size_t>(vec[i]);
            _hit_list.push_back(hit);
        }
    }
    ifs.close();       
    ifs.clear(ios::goodbit);


    //∂¡»Îinverted posting¡–±Ì
    string post_path = str_path + "posts";
    ifs.open(const_cast<char*>(post_path.c_str()),ifstream::in);
    if(ifs.fail()){
        cerr<<"open file to read posts error"<<endl; 
        return;
    } 
    while(!ifs.eof()){
        getline(ifs,str_in); 
        vector<string> vec;
        explode(str_in,"|",vec);
        int nsize=vec.size();
        for(int i=0;i<nsize;i++){
            InvertedPosting post = unserialize_inverted_posting(vec[i]);
            _inverted_posting_list.push_back(post);
        }
    }
    ifs.close();       
    ifs.clear(ios::goodbit);

    string index_path = str_path + "indexs";
    ifs.open(const_cast<char*>(index_path.c_str()),ifstream::in);
    if(ifs.fail()){
        cerr<<"open file to read index error"<<endl; 
        return;
    } 
    while(!ifs.eof()){
        getline(ifs,str_in); 
        vector<string> vec;
        explode(str_in,"|",vec);
        int nsize=vec.size();
        for(int i=0;i<nsize;i++){
            vector<string> str_vec;
            explode(vec[i],"#",str_vec);
            WordItem item;
            item.word_id = string_to_num<size_t>(str_vec[0]);
            item.begin = string_to_num<size_t>(str_vec[1]);
            item.end = string_to_num<size_t>(str_vec[2]);
            _inverted_index.insert(std::pair<size_t,WordItem>(item.word_id,item));
        }
    }
    ifs.close();       
    ifs.clear(ios::goodbit);

    string stat_path = str_path + "stat";
    ifs.open(const_cast<char*>(stat_path.c_str()),ifstream::in);
    if(ifs.fail()){
        cerr<<"open file to read stat info error"<<endl; 
        return;
    } 
    getline(ifs,str_in); 
    vector<string> vec;
    explode(str_in,"|",vec);

    _total_docs_num = string_to_num<int>(vec[0]);
    _average_length = string_to_num<int>(vec[1]);
    ifs.close();       
    ifs.clear(ios::goodbit);
    cout<<"load all end"<<endl;
}

void Searcher::load_document_index(char*path){
    FILE * file = fopen(path,"r");
    if(NULL == file){
        cerr<<"open document index to load error"<<endl; 
        return;
    } 
    while(!feof(file)){
        char buffer[1024];
        fgets(buffer,1024,file);
        vector<string> vec;
        explode(buffer,"\t",vec);
        DocumentInfo info;
        info.doc_id = string_to_num<int>(vec[0]);
        info.length = string_to_num<int>(vec[1]);
        info.label = string_to_num<int>(vec[2]);
        info.title = vec[3];
        info.url = vec[4];
        _docs_info.insert(std::pair<int,DocumentInfo>(info.doc_id,info));
    }
    fclose(file);
}

















}
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
