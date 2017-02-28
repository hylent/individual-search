/***************************************************************************
 * 
 * Copyright (c) 2016, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file ../include/indexer.h
 * @author caolin01(com@baidu.com)
 * @date 2016/06/11 14:29:34
 * @brief 
 *  
 **/

#ifndef  __INDEXER_H
#define  __INDEXER_H

#include <vector>
#include <map>
#include "segment.h"
//#include "word_dict.h"
#include "data.h"

namespace cute_engine{

const int FILE_NAME_SIZE = 128;
const int BUFFER_SIZE = 10240;
const int READ_SIZE = 10240;  //一次读入至buffer的大小


enum NAME_TYPE {
    INDEX,
    DICT,
    DOC,
    META,
};

static const char* PATH_NAME[4] = {
    "index",
    "worddict.dat",
    "docinfo.dat",
    "metainfo.dat",
};

class Indexer{
    public:
        Indexer();
        Indexer(char* path);
        ~Indexer();

        char* get_index_path();
        //建立并输出倒排索引
        //raw_data_path为原始倒排文件
        //dict_path为词典目录
        //outputpath为输出目录
        void build_inverted_index_from_file(char* raw_data_path, char* dict_path, char* output_path);
        //建立并输出文档brief信息
        //raw_data_path为原始内容文件
        //output_path为输出目录
        void build_document_info(char* raw_data_path, char* output_path);

        void caculate_document_info(const std::vector<std::string>& doc_vec, DocumentInfo& info);

        void load_document_info(char* path);
        void output_document_info(char* path) {}

        void load_metainfo(char* path);
        void output_metainfo(char* path);

        void load_worddict(char* dict_path);
        void output_worddict(char* path);

        //加载索引元数据:term对应offset等信息
        //path:数据目录
        void load_index_meta_data(char* path);

        int load_term_index(size_t term_id);

        int load_term_index(InvertedTerm* info);
        //加载term的倒排索引
        void load_inverted_index();

        void get_file_name(const char* path, NAME_TYPE type, char* output_name, size_t output_name_size, int file_index = 0);

        int get_average_length();

        int get_total_doc_num();

        //查找term词典信息
        DictInfo* get_word_info(std::string token);

        //查找term_id对应倒排中大于或等于docid的下一个文档ID
        //成功返回true,修改docid的值
        //失败返回false
        bool get_next_doc(size_t inverted_term_index, long docid, 
                                int& pos_cur, DocumentItem& item);

        std::vector<InvertedPosting>& get_inverted_posting_list();

        std::map<long, DocumentInfo>& get_docs_info();

        std::map<size_t,InvertedTerm>& get_termid_inverted_info();

        DocumentInfo* get_doc_info(long docid); 
        //加载term 倒排到索引中
        int get_doc_length(long docdid);
        
        inline InvertedTerm* get_inverted_term(const size_t& term_id) {
            std::map<size_t, size_t>::iterator iter = _inverted_index.find(term_id);
            if (iter != _inverted_index.end()){
                return  &(_inverted_term_list[iter->second]);
            }
            return NULL;
        }
        size_t add_inverted_term(const size_t& word, const InvertedTerm& item);

        
    private:

        FILE* get_index_file(unsigned int file_index);
        //void build_document_forward_index(std::string doc,int doc_id);
        //存储文档信息
        //void build_document_index(std::string &title,std::string &url,int label,int doc_id);
        //static bool forward_list_sort(ForwardItem a,ForwardItem b);
        //std::vector<Hit>& get_hit_list();
        //
        //
    private:

        //存储doc_id到文档详情信息映射
        std::map<long, DocumentInfo> _docs_info;

        //存储文档及hits索引信息
        //存储长链表
        std::vector<InvertedPosting> _inverted_posting_list;
        /*
        int _inverted_posting_list_size;
        int _inverted_posting_cur_index;
        //存储短链表
        std::vector<InvertedPosting> _short_inverted_posting_list;
        int _short_inverted_posting_list_size;
        int _short_inverted_posting_cur_index;
        */
        //存储词及对应倒排信息
        std::map<size_t, size_t> _inverted_index;
        //存储已加载或即将加载到内存的倒排词信息
        std::vector<InvertedTerm> _inverted_term_list;;
        //文档平均长度
        int _average_length;
        //文档总数
        int _total_doc_num;
    
        //FILE* _file_handles[OPEN_FILE_SIZE];
        
        char* _data_path;
        char* _buffer;

        //词典模块
        //WordDict* _pword_dict;
        std::map<std::string, DictInfo>  _dict_map;
        //打开index文件句柄
        std::map<unsigned int, FILE*> _file_handles;
};

}

#endif  //____/INCLUDE/INDEXER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
