/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
/**
 * @file searcher.h
 * @author caolin01(com@baidu.com)
 * @date 2014/06/12 20:57:29
 * @brief 
 *  
 **/

#ifndef  __SEARCHER_H_
#define  __SEARCHER_H_
#include "rank.h"
#include "data.h"
#include "segment.h"
#include "leveldb/db.h"
//#include "word_dict.h"
#include <map>
#include <string>
#include <vector>
namespace cute_engine{

struct QueryWord {
    long id;
    unsigned int df;
    unsigned int tf;
    double idf;
    double score;
    double upper_bound;
    int inverted_term_index; 
    bool is_must;
    QueryWord(){
        id = 0;
        df = 0;
        tf = 0;
        idf = 0.0;
        score = 0.0;
        is_must = false;
        inverted_term_index = -1;
    }
};

enum WordType {
    SINGLE_CHAR,
    SINGLE_NUM,
    MULTI_CHAR,
    MULTI_NUM,
    SINGLE_CHN,
    MULTI_CHN,
};

class Searcher{
    public:
        Searcher();
        ~Searcher();
        Searcher(char* index_path, char* dict_path, char* forward_db_path);
        void parse_query(std::string query_str);
        void test_search(char* path);
        static bool query_word_sort(QueryWord a, QueryWord b);
    private: 
        void init_rank(std::vector<Collector> &vec, const string& str);
        void get_result();
        void select_queryword(std::map<std::string, int>& token_tf, std::vector<QueryWord>& vec_query);
        WordType get_word_type(char* str);
        Segment* _pword_segment;
        SimRank* _prank;
        Indexer* _pindex;
        //for debug
        std::map<unsigned int, string>  _id_to_string;
        leveldb::DB* _db;
};
}

#endif  //__SEARCHER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
