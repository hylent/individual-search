/***************************************************************************
 * 
 * Copyright (c) 2016  Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 /**
 * @file segment.h
 * @author caolin
 * @date 2016/06/05 13:40:08
 * @version 1
 * @brief 
 *  
 **/
#ifndef PS_SE_SEGMENT_H
#define PS_SE_SEGMENT_H

//#include "isegment.h"
#include "Jieba.hpp"
#include "KeywordExtractor.hpp"
using std::string;

namespace cute_engine
{
static const int MAX_PATH_LEN = 1024;
static const char* const DICT_PATH = "../dict/jieba.dict.utf8";
static const char* const HMM_PATH = "../dict/hmm_model.utf8";
static const char* const USER_DICT_PATH = "../dict/user.dict.utf8";
const char* const IDF_PATH = "../dict/idf.utf8";
const char* const STOP_WORD_PATH = "../dict/stop_words.utf8";


class Segment
{
public:
    Segment(char* dict_path);

    Segment() {}

    ~Segment();

    /**
     * @brief   初始化切词 
     * @return  
     *          true: 成功   
     *          false: 失败
     * @param
     *          dict_path: 切词词典路径
     *          max_token_count: 切出的最多词数
     */
    bool init(const char *dict_path, const int max_token_count);

    /**
     * @brief   切词
     * @return  
     *          true: 切词成功
     *          false: 切词失败
     * @param
     *          str: 待切词字符串
     */
    bool segment(const char *str);

    int segment_string(char* str,std::vector<std::string>& token_vec);

    void test(char* raw_data_path,char* dict_path);

private:
    cppjieba::Jieba* _wordseg;

};
}

#endif  //PS_SE_SEGMENT_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
