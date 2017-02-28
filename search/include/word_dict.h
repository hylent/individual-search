/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
/**
 * @file word_dict.h
 * @author caolin01(com@baidu.com)
 * @date 2014/06/11 15:42:53
 * @brief 
 *  
 **/
#ifndef  __WORD_DICT_H_
#define  __WORD_DICT_H_
#include "data.h"
#include <map>
#include <string>
#include <vector>

namespace cute_engine{
/*
struct DictInfo{
    unsigned int dict_id;
    unsigned int df;
    unsigned int file_index; 
    long int offset_begin;
    long int offset_end;

    DictInfo(){
        dict_id = 0;
        df = 0;
        file_index = 0;
        offset_begin = -1;
        offset_end = -1;
    }
};*/

class WordDict{
    public:
        WordDict();
        ~WordDict();
        void load_dict(char* path);
        void output_dict(char* path);
        //新增token
        //void add_word(std::string token, int tf);
        //void add_word(std::string token, DictInfo info);
        //判断token是否存在，不存在则返回-1
        int get_word_id(std::string token);
        //查找token信息　
        //
        DictInfo* get_word_info(std::string token);
    private:
        std::map<std::string, DictInfo>  _dict_map;
};

}
#endif  //__WORD_DICT_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
