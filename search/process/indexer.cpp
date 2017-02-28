/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file indexer.cpp
 * @author caolin01(com@baidu.com)
 * @date 2014/06/11 14:27:51
 * @brief 
 *      
 **/

#include "indexer.h"
#include "data.h"
#include "util.h"
//#include "word_segment.h"
#include <iostream>
#include <fstream>

//#define DEBUG
using std::cerr;
using std::endl;
using std::cout;
using std::string;
using std::vector;
using std::map;
/*
using Json::Reader;
using Json::Value;
using Json::Writer;
*/
namespace cute_engine{
Indexer::Indexer():_pword_segment(NULL),_pword_dict(NULL){

}
Indexer::Indexer(Segment *in_segment,WordDict *in_word_dict):_pword_segment(in_segment),_pword_dict(in_word_dict){
}
Indexer::~Indexer(){
    if(NULL != _pword_segment){
        _pword_segment = NULL;
    }

    if(NULL != _pword_dict){
        _pword_dict = NULL;
    }
}
/*
void Indexer::init(char *dict_path){
    if(NULL == _pword_segment){
        _pword_segment = new Segment();
        _pword_segment->init(dict_path,1024);
    }
    if(NULL == _pword_dict){
        _pword_dict = new WordDict();
    }
}*/
//对文档集合建立正排索引
void Indexer::build_forward_index(char* raw_data_path, char* dict_path){
    FILE * file = fopen(raw_data_path,"r");
    if(NULL == file){
        cerr<<"open raw file to build index error"<<endl; 
        return;
    } 
    //init(dict_path);
    unsigned int doc_id = 0;
    unsigned int total_length = 0;
    while(!feof(file)){
        doc_id ++;
        char buffer[1024];
        fgets(buffer,1024,file);
        string doc_line(buffer);
        vector<string> doc_info_vec;
        explode(doc_line,"\t",doc_info_vec);
        if(doc_info_vec.size()!=4){
            continue;
        }
        #ifdef DEBUG
            cout<<"doc_content:"<<doc_info_vec[1]<<endl;
        #endif

        build_document_forward_index(doc_info_vec[1],doc_id);
        build_document_index(doc_info_vec[1],doc_info_vec[2],atoi(doc_info_vec[3].c_str()),doc_id);
        total_length  += doc_info_vec[1].length();
    }

    _average_length = total_length / doc_id;
    _total_doc_num = doc_id;


}
int Indexer::get_total_doc_num(){
    return _total_doc_num;
}
void Indexer::output_document_index(char*path){
    FILE * file = fopen(path,"w");
    if(NULL == file){
        cerr<<"open to write document index error"<<endl; 
        return;
    } 
    std::map<int,DocumentInfo>::iterator iter = _docs_info.begin();
    while(iter!=_docs_info.end()){
        DocumentInfo info=iter->second;
        string line = serialize_doc_info(info) + "\n"; 
        fputs(line.c_str(),file);
        ++iter;
    }
    fclose(file);
}

//对每篇文档建立document_index
void Indexer::build_document_index(string &title,string &url,int label,int doc_id){
    DocumentInfo info;
    info.title=title;
    info.url=url;
    info.label = label;
    info.length = title.length();
    info.doc_id = doc_id;
    #ifdef DEBUG
    cout<<info.title<<"=="<<info.url<<"=="<<info.label<<"=="<<info.length<<endl;
    #endif
    _docs_info.insert(std::pair<int,DocumentInfo>(doc_id,info));
}
map<int,DocumentInfo>& Indexer::get_docs_info(){
    return _docs_info;
}

//为一篇文档内容建立正排
void Indexer::build_document_forward_index(string doc_line,int doc_id){
        vector<token_t> token_vec;
        _pword_segment->segment_string(const_cast<char*>(doc_line.c_str()),token_vec);
        int count = token_vec.size();
        if( count > 0 ){
            map<string,size_t> token_df_map;
            for(int i= 0; i < count; i++){
                string token = token_vec[i].buffer;
                int token_id = _pword_dict->get_word_id(token);
                Hit hit;
                hit.pos = token_vec[i].offset;
                #ifdef DEBUG
                    cout<<token<<" pos:"<<hit.pos<<endl;
                #endif
                //存储文档词组出现信息
                ForwardItem item;
                item.word_id = token_id;
                item.doc_id = doc_id;
                item.hit = hit;
                _forward_list.push_back(item);
                token_df_map[token] = 1;
            } 

            //更新token df信息
            map<string,size_t>::iterator it = token_df_map.begin();
            while(it != token_df_map.end()){
                _pword_dict->increase_df(it->first);
                ++it;
            }
        }

}


int Indexer::get_average_length(){
    return _average_length;
}


std::map<size_t,WordItem> & Indexer::get_inverted_index(){
    return _inverted_index;
}
std::vector<InvertedPosting>& Indexer::get_inverted_posting_list(){
    return _inverted_posting_list;
}
std::vector<Hit>& Indexer::get_hit_list(){
    return _hit_list;
}

bool Indexer::forward_list_sort(ForwardItem a,ForwardItem b){
    if(a.word_id == b.word_id){
        if(a.doc_id == b.doc_id){
            return a.hit.pos < b.hit.pos;
        }else{
            return a.doc_id < b.doc_id;
        }
    }else{
       return a.word_id < b.word_id;  
    }
}
void Indexer::build_inverted_index_from_forward_index(){
    sort(_forward_list.begin(),_forward_list.end(),Indexer::forward_list_sort);
    int list_size = _forward_list.size();
    int i=0;
    int j=0;
    while(i < list_size){
        WordItem word_item;
        word_item.word_id = _forward_list[i].word_id;
        word_item.begin = _inverted_posting_list.size();

        size_t word_id = _forward_list[i].word_id;
        j = i;
        //遍历所有word_id相同项
        while(j < list_size){
            if(word_id != _forward_list[j].word_id){
                break;
            }

            InvertedPosting inverted_post;
            size_t doc_id = _forward_list[j].doc_id;
            inverted_post.doc_id = doc_id;
            inverted_post.begin = _hit_list.size();
            //遍历所有word_id、doc_id相同的信息
            while(j < list_size){
                if(_forward_list[j].word_id != word_id || _forward_list[j].doc_id != doc_id){
                    break; 
                }
                _hit_list.push_back(_forward_list[j].hit);
                j++;

            }
            inverted_post.end = _hit_list.size();
            _inverted_posting_list.push_back(inverted_post);

        }
        word_item.end = _inverted_posting_list.size();
        _inverted_index.insert(std::pair<size_t,WordItem>(word_item.word_id,word_item));
        i = j;

    }
    cout<<"end to loop"<<endl;
}

void Indexer::output_dict(char *path){
    _pword_dict->output_dict(path);
}

void Indexer::output_forward_index(char*path){

}


void Indexer::output_inverted_index(char* path){
    string str_path = string(path);
    string hit_path = str_path + "hits";
    FILE * file = fopen(const_cast<char*>(hit_path.c_str()),"w");
    if(NULL == file){
        cerr<<"open file to write hits error"<<endl; 
        return;
    } 
    int hit_size = _hit_list.size();
    string hit_str="";
    for(int i=0;i<hit_size-1;i++){
        hit_str += num_to_string<int>(_hit_list[i].pos) + "#";
    }
    hit_str += num_to_string<int>(_hit_list[hit_size-1].pos) ;
    fputs(hit_str.c_str(),file);
    fclose(file);

    
    string post_path = str_path + "posts";
    file = fopen(const_cast<char*>(post_path.c_str()),"w");
    if(NULL == file){
        cerr<<"open file to write posts error"<<endl; 
        return;
    } 
    int post_size = _inverted_posting_list.size();
    string str_out="";
    for(int i=0;i<post_size-1;i++){
        str_out += serialize_inverted_posting(_inverted_posting_list[i]) + "|";
    }
    str_out += serialize_inverted_posting(_inverted_posting_list[post_size-1]);
    fputs(str_out.c_str(),file);
    fclose(file);


    string index_path = str_path + "indexs";
    file = fopen(const_cast<char*>(index_path.c_str()),"w");
    if(NULL == file){
        cerr<<"open file to write index error"<<endl; 
        return;
    } 
    str_out="";
    map<size_t,WordItem>::iterator  invert_index_iter = _inverted_index.begin();
    while( invert_index_iter != _inverted_index.end() ){
        string word_id = num_to_string<size_t>(invert_index_iter->first);
        string begin = num_to_string<size_t>((invert_index_iter->second).begin);
        string end = num_to_string<size_t>((invert_index_iter->second).end);
        str_out += word_id + "#" + begin + "#" +end + "|"; 
        ++ invert_index_iter;
    }
    str_out += "\n";
    fputs(str_out.c_str(),file);
    fclose(file);

    string stat_path = str_path + "stat";
    file = fopen(const_cast<char*>(stat_path.c_str()),"w");
    if(NULL == file){
        cerr<<"open file to write stat info error"<<endl; 
        return;
    } 
    str_out= num_to_string<int>(_total_doc_num) + "|" + num_to_string<int>(_average_length);
    str_out += "\n";
    fputs(str_out.c_str(),file);
    fclose(file);
}




}




















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
