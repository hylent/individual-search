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
#include <cassert>
#include <sys/time.h>
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::map;
using std::ios;
using std::ifstream;
#define DEBUG

namespace cute_engine{

Searcher::Searcher(){
    _pword_segment = NULL;
    _pindex = NULL;
    _prank = NULL;
}
Searcher::Searcher(char* index_path, char* dict_path, char* forward_db_path){
    _pindex = new Indexer(index_path);
    _pword_segment = new Segment(dict_path);
    _prank = new SimRank();
    //初始化正排db 
    leveldb::Options options;
    options.create_if_missing = false;
    leveldb::Status status = leveldb::DB::Open(options, forward_db_path, &_db);
    assert(status.ok());

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
    if (NULL != _db) {
       delete _db; 
       _db = NULL;
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
    unsigned int query_index = 1;
    while(!feof(file)){
        buffer[0] = '\0';
        fgets(buffer,20480,file);
        string doc_line(buffer);
        std::vector<std::string> doc_info_vec;
        explode(doc_line,"\t",doc_info_vec);
        if (doc_info_vec.size() < (query_index + 1)) {
            continue;
        }
        string str(doc_info_vec[query_index]);
        string newstr = str.replace(str.length(), 1, "\0");
        cout << doc_info_vec[0] << "\t" << newstr << endl;
        struct timeval time_start, time_end;
        gettimeofday(&time_start, NULL);
        parse_query(doc_info_vec[query_index]);

        gettimeofday(&time_end, NULL);
        int cost_time = (time_end.tv_sec - time_start.tv_sec)*1000 + (time_end.tv_usec - time_start.tv_usec)/1000;
        cout << "\tcost_time:" << cost_time << endl;
        get_result();
        break;
    }
    cout << "process end" << endl;
}

WordType Searcher::get_word_type(char* str) {
    int len = strlen(str);
    int bytes = 0;
    int num_digit = 0;
    int num_char = 0;
    for (int i = 0; i < len;) {
        unsigned char chr = str[i];
        if (chr < 0x80) {
            if (chr >= 0x30 && chr <= 0x39) {
                num_digit ++;
            } else {
                num_char ++;
            }
            bytes = 1;
        } else if (chr >= 0xFC && chr <= 0xFD) {
            bytes = 6;
        } else if(chr >= 0xF8) {
            bytes = 5;
        } else if(chr >= 0xF0) {
            bytes = 4;
        } else if(chr >= 0xE0) {
            bytes = 3;
        } else if(chr >= 0xc0) {
            bytes = 2;
        } else {
            bytes = 1;
        }
    
        i += bytes;
    }
    //cout << " token:" << str << " len:" << len << " bytes:" << bytes << " ndigit:" << num_digit << " nchar:" << num_char << endl;
    if (len == bytes && len > 1) {
        return SINGLE_CHN;
    }
    if (len == 1) {
        if (num_char > 0) {
            return SINGLE_CHN;
        } else {
            return SINGLE_NUM;
        }
    } else if (len == num_digit){
        return MULTI_NUM;
    } else if (len == num_char){
        return MULTI_CHAR;
    }
    //8cm 作为multi_chn
    return MULTI_CHN;
}

//选择查询词，将所有词加入需读倒排列表中
void Searcher::select_queryword(std::map<std::string, int>& token_tf, std::vector<QueryWord>& vec_query) {
    vec_query.clear();
    std::map<std::string,int>::iterator token_tf_iter = token_tf.begin();
    unsigned int doc_num = _pindex->get_total_doc_num();
    while (token_tf_iter != token_tf.end()) {
        string token = token_tf_iter->first;
        WordType word_type = get_word_type(const_cast<char*>(token.c_str()));
        //单个ascii字符或汉字不拉倒排
        if (word_type == SINGLE_CHAR || word_type == SINGLE_CHN) {
            token_tf_iter++;
            #ifdef DEBUG
                cout << "pass term:" << token << " reason: word_type[" << word_type << "]"<< endl;
            #endif
            continue;
        }
        DictInfo* info = _pindex->get_word_info(token);
        if (info == NULL) {
            token_tf_iter++;
            #ifdef DEBUG
                cout << "pass term:" << token << " reason:not in worddict "<< endl;
            #endif
            continue;
        }
        if (info->df > 200000 || info->df < 100) {
            token_tf_iter++;
            #ifdef DEBUG
                cout << "pass term:" << token << " reason:df_num[" << info->df << "]" << endl;
            #endif
            continue;
        }

        //加载term索引信息
        InvertedTerm item;
        item.file_index = info->file_index;
        item.df = info->df;
        item.offset_begin = info->offset_begin;
        item.offset_end = info->offset_end;
        //strncpy(item.term, const_cast<char*>(token.c_str()), TERM_SIZE);
        //item.term[TERM_SIZE - 1] = '\0';
        int inverted_term_index =_pindex->add_inverted_term(info->dict_id, item);

        QueryWord word;
        word.id = info->dict_id;
        word.df = info->df;
        word.tf = token_tf_iter->second;
        word.idf = log((doc_num + 0.5) / ((double)(info->df + 0.5)));
        word.score = word.tf * word.idf;
        word.upper_bound = info->upper_bound;
        word.inverted_term_index = inverted_term_index;
        vec_query.push_back(word);

        token_tf_iter++;

        //for debug
        #ifdef DEBUG
        _id_to_string.insert(std::pair<unsigned int, string>(word.id, token));
        cout << " select:" << token << " id:" <<  word.id << " score:"  << word.score << " bound:" << word.upper_bound << " df:" << info->df << endl;
        #endif
    }
    /* WAND算法忽略不可省词选择
    //排序
    std::sort(vec_query.begin(), vec_query.end(), Searcher::query_word_sort);
    //选AND必查词
    for (unsigned int i = 0; i < vec_query.size() && i < NO_OMIT_WORD_NUM; i++) {
        vec_query[i].is_must = true;
        //for debug
        string str_tmp = (_id_to_string.find(vec_query[i].id))->second;
        cout <<"[" << i << "]st_must_wordid:" << vec_query[i].id << " token:" << str_tmp << endl;
    }
    //cout << " final_size:" << vec_query.size() << endl;
    */
}

bool Searcher::query_word_sort(QueryWord a, QueryWord b) {
    return a.score > b.score; 
}

void Searcher::parse_query(string query_str) {
#ifdef DEBUG
    cout << "query_str:" << query_str << endl;
#endif
    //需要增加对query预处理：比如大小写转换等功能
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
        //初始化存储查询词、对应倒排等相关信息
        //gettimeofday(&time_start, NULL);
        _pindex->load_term_index(query_iter->id);
        //get_time_space(time_start, " parser_query_load_index ");

        Collector collector(_pindex);
        collector._word_id = query_iter->id;
        collector._tf = query_iter->tf;
        collector._idf = query_iter->idf;
        collector._pos_cur = -1;
        collector._upper_bound = query_iter->upper_bound;
        collector._inverted_term_index = query_iter->inverted_term_index;
        collector_vec.push_back(collector);
        
        #ifdef DEBUG

            string token_tmp = (_id_to_string.find(query_iter->id))->second;
            cout << "token" << token_tmp << " term_id:" << collector._word_id << " tf:" << collector._tf << " idf:" << collector._idf << endl;
        #endif
        query_iter++;
    }
    #ifdef DEBUG
        cout << " begin init_rank:" << endl;
    #endif 
    init_rank(collector_vec, query_str);
}

void Searcher::init_rank(std::vector<Collector> &vec, const string& str){
    _prank->set_collector_vec(vec);
    _prank->set_query_str(str);
    _prank->set_forward_db(_db);
    //struct timeval time_begin, time_end;
    //gettimeofday(&time_begin, NULL);

    _prank->rank_docs();

    //get_time_space(time_begin, " first_rank ");

    //gettimeofday(&time_begin, NULL);
    _prank->precise_rank_docs();

    //get_time_space(time_begin, " second_rank ");
}

void Searcher::get_result() {
    std::vector<DocScore> docs_score = _prank->get_docs_score();
    //按打分值从大到小排序
    //std::sort_heap(docs_score.begin(),docs_score.end(),Rank::score_sort);
    std::sort(docs_score.begin(),docs_score.end(),Rank::precise_score_sort);
    std::vector<DocScore>::iterator iter = docs_score.begin();
    cout << "final_result: ";
    while(iter != docs_score.end()){
        size_t doc_id = iter->doc_id;
        double score = iter->doc_score;
        cout << doc_id << ":" << iter->precise_score << "|" << score << " ";
        iter++;
    }
    cout << endl;
}

}
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
