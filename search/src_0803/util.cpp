/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file util.cpp
 * @author caolin01(com@baidu.com)
 * @date 2014/06/16 13:39:20
 * @brief 
 *  
 **/


#include "util.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

namespace cute_engine{
    
    void explode(std::string str,std::string sep,std::vector<std::string> &vec){
        vec.clear();
        size_t begin = 0;
        size_t end = std::string::npos;

        while((end = str.find(sep,begin)) != std::string::npos){
            if(end > begin){
                std::string found_str = str.substr(begin, end - begin);
                vec.push_back(found_str);
            }   
            begin = end + 1;
        }   
        if(begin < str.length()){
            std::string found_str = str.substr(begin,end - begin);
            vec.push_back(found_str);
        }
    }

    std::string implode(std::vector<std::string> & vec,std::string sep) {
        int size = vec.size();
        if(size<=0) return "";
        std::string ret_str="";
        for(int i=0;i<size-1;++i){
            ret_str += vec[i] + sep;
        }
        ret_str += vec[size-1];
        return ret_str;
    }
/*    
    std::string serialize_hit(Hit hit){
        return num_to_string<int>(hit.pos);
    }

    Hit unserialize(std::string pos){
        int npos=string_to_num<int>(pos);
        Hit hit(npos);
        return hit;
    }
    std::string serialize_forward_post(ForwardPosting post){
        std::vector<Hit> hits = post.hits;
        int nsize = hits.size();
        std::string ret = num_to_string<int>(post.word_id) + ",";
        for(int i=0;i<nsize-1;i++){
            ret += serialize_hit(hits[i]) + "#";            
        }
        ret += serialize_hit(hits[nsize-1]);            
        return ret;
    }
    std::string unserialize(ForwardPosting post){
    
    }

*/

    std::string serialize_inverted_posting(InvertedPosting post){
        std::string ret="";
        ret += num_to_string<size_t>(post.doc_id) + "#";
        ret += num_to_string<size_t>(post.tf) + "#";
        return ret;
    }

    InvertedPosting unserialize_inverted_posting(std::string instr){
        std::vector<std::string> vec;
        explode(instr,"#",vec);
        InvertedPosting post;
        post.doc_id = string_to_num<size_t>(vec[0]);
        post.tf = string_to_num<size_t>(vec[1]);
        return post;
    }

    std::string serialize_doc_info(const DocumentInfo& info){
        std::vector<std::string> vec;
        vec.push_back(num_to_string<long>(info.doc_id));
        vec.push_back(num_to_string<int>(info.subject));
        vec.push_back(num_to_string<int>(info.spider_source));
        vec.push_back(num_to_string<int>(info.doc_len));
 //       vec.push_back(info.content);
//      vec.push_back(num_to_string<double>(info.norm_value));
        std::string str=implode(vec,"\t");
        return str;
    }

}
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
