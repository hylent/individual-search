/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file word_dict.cpp
 * @author caolin01(com@baidu.com)
 * @date 2014/06/11 15:51:49
 * @brief 
 *  
 **/

#include "word_dict.h"
#include "util.h"
#include<vector>

namespace cute_engine{
using std::string;
using std::map;
using std::cout;
using std::endl;
using std::cerr;
using std::vector;

WordDict::WordDict(){
}

WordDict::~WordDict(){
}

int WordDict::get_word_id(string token){
    map<string,DictInfo>::iterator it = _dict_map.find(token);
    if(it!= _dict_map.end()){
        return (it->second).dict_id;
    }
    DictInfo info;
    info.dict_id = _dict_map.size() + 1;
    info.df = 0;
    _dict_map.insert(std::pair<string,DictInfo>(token,info));
    return info.dict_id;
}

void WordDict::increase_df(string token){
    map<string,DictInfo>::iterator it = _dict_map.find(token);
    if(it!= _dict_map.end()){
        ++ (it->second).df;
    }
}

DictInfo WordDict::get_word_info(std::string token){
    map<string,DictInfo>::iterator it = _dict_map.find(token);
    if(it!= _dict_map.end()){
        return it->second;
    }
    DictInfo info;
    info.dict_id = -1;
    return info;
}

void WordDict::load_dict(char* path){

    FILE * file = fopen(path,"r");
    if(NULL == file){
        cerr<<"open raw file error"<<endl; 
        return;
    }   
    while(!feof(file)){
        char buffer[1024];
        fgets(buffer,1024,file);
        vector<string> buffer_vec;
        explode(buffer,"\t",buffer_vec);
        string token = buffer_vec[0];
        int dict_id = string_to_num<int>(buffer_vec[1]);
        int df = string_to_num<int>(buffer_vec[2]);
        DictInfo info;
        info.dict_id = dict_id;
        info.df = df;
        _dict_map.insert(std::pair<string,DictInfo>(token,info) );
    }   
    fclose(file);
}

void WordDict::output_dict(char* path){
    FILE * file = fopen(path,"w");
    if(NULL == file){
        cerr<<"open raw file error"<<endl; 
        return;
    }   
    std::map<string,DictInfo>::iterator iter = _dict_map.begin();
    while(iter != _dict_map.end()){
        string line = iter->first+"\t";
        line += num_to_string<int>( (iter->second).dict_id) + "\t";
        line += num_to_string<int>( (iter->second).df ) + "\n";
        fputs(line.c_str(),file);
        ++iter;
    }   
    fclose(file);
}

}






















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
