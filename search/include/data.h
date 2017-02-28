/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
/**
 * @file data.h
 * @author caolin01(com@baidu.com)
 * @date 2014/06/13 13:43:18
 * @brief 
 *  
 **/

#ifndef  __DATA_H_
#define  __DATA_H_
#include<iostream>
#include<vector>
#include<string> 
#include <stdio.h>

#define PDEBUG 0
#if PDEBUG
#   define dprintf(...) fprintf(stderr, __VAR_ARGS__)
#else
#   define dprintf(...)
#endif
namespace cute_engine{


const unsigned int NO_OMIT_WORD_NUM = 0;
const int TERM_SIZE = 56;

struct Hit{
    size_t pos;
};
struct ForwardItem{
    size_t term_id;
    size_t doc_id;
    Hit hit;
};
//词典项
struct DictInfo{
    unsigned int dict_id;
    unsigned int df;
    unsigned int file_index; 
    long int offset_begin;
    long int offset_end;
    double upper_bound;
    DictInfo(){
        dict_id = 0;
        df = 0;
        file_index = 0;
        offset_begin = -1;
        offset_end = -1;
        upper_bound = 0.0;
    }
};

enum LOADTYPE {
    NOT_LOAD,
    PART_LOAD,
    COMPLETE_LOAD
};
//index加载到内存中term信息
struct InvertedTerm{
    int pos_begin;   //Posting_list的下标
    int pos_end;
    int pos_cur;
    unsigned int file_index; //目前遍历到文档列表的下标位置
    unsigned int df;
    long  offset_begin;
    long  offset_end;
    long offset_cur;
    LOADTYPE load_type; 
//    char term[TERM_SIZE];
    InvertedTerm() {
        file_index = 0;
        df = 0;
        offset_begin = -1;
        offset_end = -1;
        offset_cur = 0;
        pos_begin = -1;
        pos_end = -1;
        pos_cur = -1;
        load_type = NOT_LOAD;
    }
    InvertedTerm(unsigned int in_file_index, unsigned int in_df, long in_begin, long in_end) {
  //      strncpy(term, instr, TERM_SIZE);
  //      term[TERM_SIZE - 1] = '\0';
        file_index = in_file_index;
        df = in_df;
        offset_begin = in_begin;
        offset_end = in_end;
        offset_cur = 0;
        pos_begin = -1;
        pos_end = -1;
        pos_cur = -1;
        load_type = NOT_LOAD;
    }
};
struct InvertedPosting{
    long doc_id;
    size_t tf;
//    size_t begin;
//    size_t end;
};

//文档brief信息
struct DocumentInfo{
    //long doc_id; 
    int doc_len;
    //int subject;
    //int spider_source;
    // std::string content;
};

//文档倒排每项的信息
struct DocumentItem{
    long doc_id;
    int tf;
    int doc_len;
    DocumentItem() {
        doc_id = 0;
        tf = -1;
        doc_len = -1;
    }
};

}


#endif  //__DATA_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
