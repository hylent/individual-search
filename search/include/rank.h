/***************************************************************************
 * 
 * Copyright (c) 2016, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
/**
 * @file include/Rank.h
 * @author caolin
 * @date 2016/06/12 20:50:38
 * @brief 
 *  
 **/

#ifndef  __RANK_H
#define  __RANK_H
#include "data.h"
#include "util.h"
#include "leveldb/db.h"
#include "indexer.h"
#include <vector>
#include <map>
namespace cute_engine{

const unsigned int MAX_QUERY_WORD_LENGTH = 250;
const unsigned int MAX_QUERY_BYTE_LENGTH = MAX_QUERY_WORD_LENGTH * 3;

class Collector{
    public:
        Collector() {}
        Collector(Indexer* inpar);
        ~Collector();
        long get_doc_id();
        int get_word_id();

        int get_query_tf();
        double get_query_idf();

        //查询词在文档中出现的次数
        int get_query_doc_tf();
        //遍历到大于或等于doc_id的下一篇文档
        //列表遍历完毕或未查找到则返回-1
        long get_next_doc(long doc_id = 0);
        //判断倒排中是否还有未遍历文档(doc_id并不变化)
        bool next();

        int get_doc_length();
        int get_average_length();

        double get_upper_bound();
    public:
        int _word_id;
        DocumentItem _item;
        int _tf;     //查询词在query中tf
        double _idf; //查询词idf
        Indexer* _indexer;
        int _pos_cur;  // 遍历倒排的位置
        float _upper_bound;  //对文档贡献上限
        int _inverted_term_index;  //在Index的inverted_index中的下标
};

struct DocScore{
    long doc_id;
    double doc_score;     //第一次排序打分
    double precise_score; //第二次排序打分
};

class Rank{
    public:
        Rank();
        Rank(const std::vector<Collector>& invec);
        virtual ~Rank();
        virtual void rank_docs();
        static bool collector_sort(Collector& a, Collector& b);
        static bool score_sort(const DocScore& a, const DocScore& b);
        static bool precise_score_sort(const DocScore& a, const DocScore& b);
        std::vector<DocScore> get_docs_score();
        virtual long get_next_doc(long in_doc_id);
        virtual void set_collector_vec(const std::vector<Collector>& invec);

    protected:
        std::vector<DocScore> _score_vec;
        std::vector<Collector> _collector_vec;
};

class SimRank:public Rank{
    public:
        SimRank();
        ~SimRank();
        SimRank(std::vector<Collector> invec);
        void rank_docs();
        void precise_rank_docs();
        double get_score(Collector& collector);
        void init_term_posting();
        long get_next_doc(long in_doc_id);
        static bool posting_sort(const std::pair<int, long>&a, const std::pair<int, long>& b);

        int find_pivot_term(const std::vector<std::pair<int, long> >& posting, double threshod);
        int get_next_doc_wand(double threshold, long& ret_doc_id);

        int advance_term(int posting_index, long next_doc_id);

        void insert_sort(int index);

        void set_query_str(const std::string& str);

        void set_forward_db(leveldb::DB* in_db);
        
    private:

        int get_string_token_len(const std::string& str, std::vector<std::pair<int, int> >& token_len);

        bool compare_token(const std::string& str1, const std::string& str2, const std::pair<int, int>& pair1, const std::pair<int, int>& pair2);

        string longest_common_string(const std::string& str1, const std::string& str2, 
                            const std::vector<std::pair<int, int> >& tokens_len1, 
                            const std::vector<std::pair<int, int> >& tokens_len2);
    private:
        //记录当前所有term遍历到的doc_id, 目的是加快sort
        //pair<int _collector_vec_index, long term_cur_doc_id>
        std::vector<std::pair<int, long> > _cur_term_posting; 
        long _cur_doc_id;   //当前处理过的文档id, DocumentAtATime
        //char _query_str[MAX_QUERY_BYTE_LENGTH];

        leveldb::DB* _forward_db;
        //
        int _strlen[MAX_QUERY_WORD_LENGTH][MAX_QUERY_WORD_LENGTH];
        int _path[MAX_QUERY_WORD_LENGTH][MAX_QUERY_WORD_LENGTH];
        std::string _query_str;
};

}
#endif  //__INCLUDE/RANK_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
