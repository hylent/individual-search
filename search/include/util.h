/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file util.h
 * @author caolin01(com@baidu.com)
 * @date 2014/06/16 14:07:35
 * @brief 
 *  
 **/




#ifndef  __UTIL_H_
#define  __UTIL_H_


#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <sys/time.h>
#include "data.h"

namespace cute_engine{

    
    template<class Type>
    Type string_to_num(std::string str){
        std::istringstream iss(str);
        Type num;
        iss>>num;
        return num;
    }
   
    template<class Type>
    std::string num_to_string(Type num){
        std::ostringstream oss;
        oss<<num;
        std::string str;
        return oss.str();
    } 

    void explode(std::string str,std::string sep,std::vector<std::string> &vec);

    std::string implode(std::vector<std::string> & vec,std::string sep);

    int get_time_space(const struct timeval& time_start, const char* msg);
    
/*
    std::string serialize_hit(Hit hit);

    Hit unserialize(std::string pos);
*/
    std::string serialize_inverted_posting(InvertedPosting post);

    InvertedPosting unserialize_inverted_posting(std::string instr); 
    
    std::string serialize_doc_info(const DocumentInfo& info);


}

#endif  //__UTIL_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
