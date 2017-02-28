/***************************************************************************
 * 
 * Copyright (c) 2016, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file word_dict.cpp
 * @author caolin
 * @date 2016/06/11 15:51:49
 * @brief 
 *  
 **/

#include "word_dict.h"
#include "util.h"
#include <vector>
#include <stdio.h>

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
    return -1;
}

DictInfo* WordDict::get_word_info(std::string token){
    map<string,DictInfo>::iterator it = _dict_map.find(token);
    if(it!= _dict_map.end()){
        return &(it->second);
    }
    return NULL;
}

void WordDict::load_dict(char* path){

    FILE * file = fopen(path,"r");
    if(NULL == file){
        cerr<<"load worddict_file error: " << path << endl; 
        return;
    }   
    char buffer[1024];
    while(!feof(file)){
        fgets(buffer,1024,file);
        vector<string> buffer_vec;
        explode(buffer,"\t",buffer_vec);
        string token = buffer_vec[0];

        DictInfo info;
        info.df = string_to_num<long>(buffer_vec[1]);
        info.dict_id = string_to_num<long>(buffer_vec[2]);
        if (buffer_vec.size() > 3) {
            info.file_index = string_to_num<long>(buffer_vec[3]);
            info.offset_begin = string_to_num<long>(buffer_vec[4]);
            info.offset_end = string_to_num<long>(buffer_vec[5]);
        }

        #ifdef DEBUG
            printf("%s\t%u\t%u\t%u\t%ld\t%ld\n", const_cast<char*>(token.c_str()), info.df, info.dict_id, info.file_index, info.offset_begin, info.offset_end);
        #endif 
        _dict_map.insert(std::pair<string,DictInfo>(token,info) );
    }   
    fclose(file);
}

void WordDict::output_dict(char* path){
    FILE * file = fopen(path,"w");
    if(NULL == file){
        cerr<<"open worddict_file to write error: " << path << endl; 
        return;
    }   
    std::map<string,DictInfo>::iterator iter = _dict_map.begin();
    const int SIZE = 512;
    char buffer[SIZE];
    while(iter != _dict_map.end()){
        string word = iter->first+"\t";
        DictInfo& info = iter->second;
        snprintf(buffer, SIZE, "%s\t%u\t%u\t%u\t%ld\t%ld\n", const_cast<char*>(word.c_str()), info.df, info.dict_id, info.file_index, info.offset_begin, info.offset_end);
        fputs(buffer,file);
        ++iter;
    }   
    fclose(file);
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
