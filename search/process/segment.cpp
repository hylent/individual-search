/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 /**
 * @file segment.cpp
 * @author lichenggang(lichenggang@baidu.com)
 * @date 2014/06/05 13:37:14
 * @version 1
 * @brief 
 *  
 **/

#include "segment.h"

using std::cerr;
using std::endl;
using std::string;
namespace cute_engine
{
Segment::Segment()
{
    _pscw_dict = NULL;
    _pscw_out = NULL;
}

Segment::~Segment()
{
    if (_pscw_dict)
    {
       scw_destroy_worddict(_pscw_dict);
       _pscw_dict = NULL;
    }
    if (_pscw_out)
    {
        scw_destroy_out(_pscw_out);
        _pscw_out = NULL;
    }   
}

bool Segment::init(const char *dict_path, const int max_token_count)
{
    if (NULL == dict_path)
    {
        return false; 
    }

    if (NULL == (_pscw_dict = scw_load_worddict(dict_path)))
    {
        return false;
    }
    if (NULL == (_pscw_out = scw_create_out(max_token_count * 5, SCW_OUT_ALL | SCW_OUT_PROP)))
    {
        return false;
    }

    return true;
}

bool Segment::segment(const char *str)
{
    if (NULL == str)
    {
        return false;
    }
    scw_segment_words(_pscw_dict, _pscw_out, str, strlen(str), 1);
    return true;
}

int Segment::get_token(token_t tokens[], const int size, const TokenType token_type)
{
    int token_count = scw_get_token_1(_pscw_out, token_type, tokens, size);
    return token_count;
}

void Segment::segment_string(char* str,std::vector<token_t> & token_vec){

    if(!segment(str)){
        cerr<<"FATAL: fail to segment str"<<endl;
        return;
    }
    token_t tokens[1024];
    int token_count=0;
    token_count = get_token(tokens,1024,TOKEN_BASIC);
    token_vec.clear();
    for(int i=0;i<token_count;i++){
        token_vec.push_back(tokens[i]);
    }
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

        vector<string> doc_info_vec;
        size_t begin = 0;
        size_t end = std::string::npos;
        while( (end = doc_line.find("\t",begin) ) != std::string::npos){
            if(end>begin){
                string found_str = doc_line.substr(begin,end - begin);
                doc_info_vec.push_back(found_str);
            }
            begin = end + 1;
        }
        vector<token_t> token_vec;
        segment_string(const_cast<char*>(doc_info_vec[1].c_str()),token_vec);
        int count = token_vec.size();
        for(int i=0;i<count; i++){
            string token = token_vec[i].buffer;
            int pos = token_vec[i].offset;
            std::cout<<token<<"-"<<pos<<std::endl;
        }
    }
}

}

/* vim: set ts=4 sw=4 sts=4 tw=100 */
