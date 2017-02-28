/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 /**
 * @file test_seg.cpp
 * @author lichenggang(lichenggang@baidu.com)
 * @date 2014/06/05 15:04:23
 * @version 1
 * @brief 
 *  
 **/

#include <iostream>
#include <vector>
#include <string>
#include "segment.h"

using std::cerr;
using std::cout;
using std::endl;
using std::vector;
using cute_engine::Segment;
//using cute_engine::TOKEN_BASIC;

int main(int argc, char *argv[])
{
    if (2 != argc)
    {
        cerr << "USAGE: " << argv[0] << " dict_path" << endl;
        return -1;
    }
    char *dict_path = argv[1];

    // init segment
    Segment *psegment = NULL;
    try
    {
        psegment = new Segment(dict_path);
    }
    catch (std::bad_alloc)
    {
        cerr << "FATAL: fail to alloc Segment" << endl;
        return -1;
    }
    if (!psegment->init(dict_path, 1024))
    {
        cerr << "FATAL: fail to init Segment" << endl;
        return -1;
    }

    // segment words
    const char *str = "中华人民共和国宇宙中心阿凡题公司";
    if (!psegment->segment(str))
    {
        cerr << "FATAL: fail to segment str[" << str << "]" << endl;
        return -1;
    }

    // get segment result
    /*
    token_t tokens[1024];
    int token_count = 0;
    token_count = psegment->get_token(tokens, 1024, TOKEN_BASIC);
    for (int i = 0; i < token_count; ++i)
    {
        cout << "term=[" << tokens[i].buffer << "] "
             << "off=["  << tokens[i].offset << "] "
             << "len=["  << tokens[i].length << "]" << endl;
    }*/

    std::vector<std::string> vec;
    int token_count = 0;
    token_count = psegment->segment_string(const_cast<char*>(str), vec);
    for (int i = 0; i < token_count; ++i)
    {
        cout << "term=[" << vec[i] << "] " << endl;
    }

    if (psegment)
    {
        delete psegment;
        psegment = NULL;
    }

    return 0;;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 */
