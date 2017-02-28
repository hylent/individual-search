/***************************************************************************
 * 
 * Copyright (c) 2016, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file process/searcher.cpp
 * @author caolin01
 * @date 2016/06/12 21:20:07
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

//#define DEBUG
namespace cute_engine{

Searcher::Searcher(){
    _pword_segment = NULL;
    _pindex = NULL;
    _prank = NULL;
}
Searcher::Searcher(char* index_path, char* dict_path){
    _pindex = new Indexer(index_path);
    _pword_segment = new Segment(dict_path);
    _prank = new SimRank();
}
Searcher::~Searcher(){
    if (NULL != _pword_segment) {
        delete _pword_segment;
        _pword_segment = NULL;
    }
    if (NULL != _pindex) {
        delete _pindex;
        _pindex = NULL;
    }
    if (NULL != _prank) {
        delete _prank;
        _prank = NULL;
    }
}

void Searcher::test_search(char* raw_path){
    _pindex->load_index_meta_data(_pindex->get_index_path());
    FILE * file = fopen(raw_path,"r");
    if(NULL == file){
        cerr<<"open raw file to search error"<<endl; 
        return;
    } 
    char buffer[20480];
    while(!feof(file)){
        fgets(buffer,20480,file);
        string doc_line(buffer);
        std::vector<std::string> doc_info_vec;
        explode(doc_line,"\t",doc_info_vec);
/*
        if(doc_info_vec.size()!=4){
            continue;
        } */
        cout << doc_info_vec[0] << "\t" << doc_info_vec[3] << endl;
        parse_query(doc_info_vec[3]);
        get_result();
    }
    cout << "process end" << endl;
}

//选择两个必查词，将所有词加入需读倒排列表中
void Searcher::select_queryword(std::map<std::string, int>& token_tf, std::vector<QueryWord>& vec_query) {
    std::map<std::string,int>::iterator token_tf_iter = token_tf.begin();
    unsigned int doc_num = _pindex->get_total_doc_num();
    while (token_tf_iter != token_tf.end()) {
        string token = token_tf_iter->first;
        DictInfo* info = _pindex->get_word_info(token);
        if (info == NULL) {
            token_tf_iter++;
            //cout << "no index:term not in dict: " << token << endl;
            continue;
        }
        QueryWord word;
        word.id = info->dict_id;
        word.df = info->df;
        word.tf = token_tf_iter->second;
        word.idf = log((doc_num + 0.5) / ((double)(info->df + 0.5)));
        word.score = word.idf;
        #ifdef DEBUG
            cout << " token:" << token << " token_id:" << word.id << word.score << endl;
        #endif
        vec_query.push_back(word);

        WordItem item;
        item.file_index = info->file_index;
        item.df = info->df;
        item.offset_begin = info->offset_begin;
        item.offset_end = info->offset_end;
        //strncpy(item.term, const_cast<char*>(token.c_str()), TERM_SIZE);
        //item.term[TERM_SIZE - 1] = '\0';
        _pindex->add_inverted_term(word.id, item);
        token_tf_iter++;
        _id_to_string.insert(std::pair<unsigned int, string>(word.id, token));
    }
    //排序
    std::sort(vec_query.begin(), vec_query.end(), Searcher::query_word_sort);
    
    //选两个必查词
    if (vec_query.size() > 0) {
        vec_query[0].is_must = true;
        //#ifdef DEBUG
           map<unsigned int,string>::iterator iter_tmp =  _id_to_string.find(vec_query[0].id);
            string str_tmp = iter_tmp->second; 
            cout << "1st_must_word_id:" << vec_query[0].id << " token:" << str_tmp << endl;
        //#endif
    }
    if (vec_query.size() > 1) {
        vec_query[1].is_must = true;
        //#ifdef DEBUG
           string str_tmp = (_id_to_string.find(vec_query[1].id))->second; 
            cout << "2nd_must_word_id:" << vec_query[1].id << "token" << str_tmp << endl;
        //#endif
    }
}

bool Searcher::query_word_sort(QueryWord a, QueryWord b) {
    return a.score > b.score; 
}

void Searcher::parse_query(string query_str) {
#ifdef DEBUG
    cout << "query_str:" << query_str ;
#endif
    //切词　
    std::vector<std::string> token_vec;
    _pword_segment->segment_string(const_cast<char*>(query_str.c_str()),token_vec);
    int count = token_vec.size();
    if(count <= 0) {
        cerr << "segment_error:no_seg q:" << query_str  << endl;
    }
    //计算查询query=>tf
    map<string,int> token_tf;
    for(int i = 0; i < count; i++){
        string token = token_vec[i];
        map<string,int>::iterator iter = token_tf.find(token);
        if(iter != token_tf.end()){
            ++ iter->second; 
        }else{
            token_tf.insert(std::pair<string, int>(token,1)); 
        }
    }

    //选择必选词
    std::vector<QueryWord> vec_query;
    select_queryword(token_tf, vec_query);

    //遍历查询词,加载索引
    std::vector<Collector> collector_vec;
    std::vector<QueryWord>::iterator query_iter = vec_query.begin();
    while (query_iter != vec_query.end()) {
        /*
        if (query_iter->df > 1000000) {
            query_iter++;
            continue;
        }*/
        //初始化存储查询词、对应倒排等相关信息
        _pindex->load_term_index(query_iter->id);

        Collector collector(_pindex);
        collector._word_id = query_iter->id;
        collector._tf = query_iter->tf;
        collector._idf = query_iter->idf;
        collector_vec.push_back(collector);
        #ifdef DEBUG
            string token = (_id_to_string->find(collector._word_id))->second;
            cout << "load_suc_index term:" << token << " tf:" << collector._tf << " idf:" << collector._idf << endl;
        #endif
        query_iter++;
    }
    #ifdef DEBUG
        cout << " begin init_rank:" << endl;
    #endif 
    init_rank(collector_vec);

}

void Searcher::init_rank(std::vector<Collector> &vec){
    _prank->set_collector_vec(vec);
    _prank->rank_docs();
}

void Searcher::get_result(){
    std::vector<DocScore> docs_score = _prank->get_docs_score();
    //按打分值从大到小排序
    std::sort_heap(docs_score.begin(),docs_score.end(),Rank::score_sort);
    std::vector<DocScore>::iterator iter = docs_score.begin();
    int line=1;
    while(iter != docs_score.end()){
        size_t doc_id = iter->doc_id;
        double score = iter->doc_score;
        cout << doc_id << ":" << score << " ";
        line++;    
        iter++;
    }
    cout << endl;
}

}
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
