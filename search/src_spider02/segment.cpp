/***************************************************************************
 * 
 * Copyright (c) 2016, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 /**
 * @file segment.cpp
 * @author caolin(lin.cao@lejent.com)
 * @date 2016/06/05 13:37:14
 * @version 1
 * @brief 
 *  
 **/

#include "segment.h"
#include <vector>
#include <string>

using std::cerr;
using std::endl;
using std::string;
namespace cute_engine
{
Segment::Segment(char* path)
{

    string path_str(path);
    string DICT_PATH = path_str + "/jieba.dict.utf8";
    string HMM_PATH = path_str + "/hmm_model.utf8";
    string USER_DICT_PATH = path_str + "/user.dict.utf8";
    _wordseg = new cppjieba::Jieba(DICT_PATH.c_str(),
        HMM_PATH.c_str(),
        USER_DICT_PATH.c_str());
}

Segment::~Segment()
{
    delete _wordseg;
    _wordseg = NULL;
}

bool Segment::init(const char *dict_path, const int max_token_count)
{
    return true;
}

bool Segment::segment(const char *str)
{
    return true;
}

int Segment::segment_string(char* str,std::vector<std::string>& vec){
    vec.clear();
    _wordseg->Cut(str, vec);
    return vec.size();
    #ifdef DEBUG
        std::cout << limonp::Join(vec.begin(), vec.end(), "/") << std::endl;
    #endif
}


void Segment::test(char* raw_data_path,char* dict_path){
    FILE * file = fopen(raw_data_path,"r");
    if(NULL == file){
        cerr<<"open raw file error"<<endl; 
        return;
    } 
    init(dict_path,1024);
    while(!feof(file)){
        char buffer[1024];
        fgets(buffer,1024,file);
        string doc_line(buffer);

        std::vector<std::string> doc_info_vec;
        size_t begin = 0;
        size_t end = std::string::npos;
        while( (end = doc_line.find("\t",begin) ) != std::string::npos){
            if(end>begin){
                string found_str = doc_line.substr(begin,end - begin);
                doc_info_vec.push_back(found_str);
            }
            begin = end + 1;
        }
        std::vector<std::string> token_vec;
        segment_string(const_cast<char*>(doc_info_vec[3].c_str()), token_vec);
        int count = token_vec.size();
        for(int i = 0; i < count; i++) {
            string token = token_vec[i];
            std::cout << token << "-" << std::endl;
        }
    }
}

}

/* vim: set ts=4 sw=4 sts=4 tw=100 */
