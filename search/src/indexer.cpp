/***************************************************************************
 * 
 * Copyright (c) 2016 Afanti, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
/**
 * @file indexer.cpp
 * @author caolin01
 * @date 2016/06/11 14:27:51
 * @brief 
 *      
 **/

#include "indexer.h"
#include "data.h"
#include "util.h"
//#include "word_segment.h"
#include <iostream>
#include <fstream>

//#define DEBUG
//#define TRACE
using std::cerr;
using std::endl;
using std::cout;
using std::string;
using std::vector;
using std::map;
namespace cute_engine{
Indexer::Indexer(){
    _buffer = new char[BUFFER_SIZE];
    _data_path = new char[FILE_NAME_SIZE];
    _data_path[FILE_NAME_SIZE - 1] = '\0';
}

Indexer::Indexer(char* path){
    _buffer = new char[BUFFER_SIZE];
    _data_path = new char[FILE_NAME_SIZE];
    strncpy(_data_path, path, FILE_NAME_SIZE);
    _data_path[FILE_NAME_SIZE - 1] = '\0';
    //_pword_dict = new WordDict();
    /*
    _inverted_posting_list_size = 200000000;
    _inverted_posting_cur_index = 0;
    _inverted_posting_list.resize(_inverted_posting_list_size);
    _short_inverted_posting_list_size = 50000000;
    _short_inverted_posting_cur_index = 0;
    _short_inverted_posting_list.resize(_short_inverted_posting_list_size);
    */

    std::map<unsigned int, FILE*>::iterator iter = _file_handles.begin();
    while (iter != _file_handles.end()) {
        FILE* file = iter->second;
        if (file != NULL) {
            fclose(file);
        }
        iter++;
    }
}
Indexer::~Indexer(){
    if (_buffer != NULL) {
        delete _buffer;
        _buffer = NULL;
    }
    if (_data_path != NULL) {
        delete _data_path;
        _buffer = NULL;
    }
}
/*
void Indexer::build_term_upper_bound(char* raw_data_path, char* index_path, char* dict_path) {
    if (_dict_map.empty()) {
        load_worddict(dict_path);
    }
    if (_docs_info.empty()) {
        load_document_info(index_path);
    }
    if (_average_length <= 0 || _total_doc_num <= 0) {
        load_metainfo(index_path);
    }

}*/

//对文档集合建立brief并输出
void Indexer::build_document_info(char* raw_data_path, char* output_path){
    FILE * file = fopen(raw_data_path, "r");
    if(NULL == file){
        cerr<<"open raw file to build forward_index error:" << raw_data_path << endl; 
        return;
    } 

    char output_name[FILE_NAME_SIZE];
    get_file_name(output_path, DOC, output_name, FILE_NAME_SIZE);
    FILE * doc_file = fopen(output_name, "w");
    if(NULL == file){
        cerr<<"open file to write document_info error: " << output_name << endl; 
        return;
    }

    unsigned int doc_id = 0;
    long int total_length = 0;
    //char buffer[10240];
    //DocumentInfo info;
    vector<string> doc_info_vec;
    char buffer[128];
    while(!feof(file)){
        fgets(_buffer, BUFFER_SIZE, file);
        string doc_line(_buffer);
        explode(doc_line,"\t",doc_info_vec);
        if(doc_info_vec.size() < 4){
            continue;
        }
        //#ifdef DEBUG
        //    cout << "doc_content:" << doc_info_vec[3] <<endl;
        //#endif
        /*
        caculate_document_info(doc_info_vec, info);
        string info_str = serialize_doc_info(info);
        #ifdef DEBUG
            cout << "doc_info_str:" << info_str << endl;
        #endif
        */
        int doc_len = doc_info_vec[3].length();
        snprintf(buffer, 128, "%s\t%d\n", const_cast<char*>(doc_info_vec[0].c_str()), doc_len);
        fputs(buffer, doc_file);
        total_length += doc_info_vec[3].length();
        doc_id++;
    }
    if (doc_id != 0) {
        _average_length = total_length / doc_id;
    } else {
        _average_length = 50; // 默认值
    }
    _total_doc_num = doc_id;
    fclose(file);
    fclose(doc_file);
    output_metainfo(output_path);
}

//对每篇文档建立brief信息
void Indexer::caculate_document_info(const std::vector<std::string>& doc_vec, DocumentInfo& info){
    //info.doc_id = string_to_num<long>(doc_vec[0]);
    //info.subject = string_to_num<int>(doc_vec[1]);
    //info.spider_source = string_to_num<int>(doc_vec[2]);
    //info.content = string_to_num<int>(doc_vec[3]);
    info.doc_len = (doc_vec[3]).length();
    //暂定
    #ifdef DEBUG
//cout<<info.doc_id <<"\t"<<info.subject<<"\t"<<info.spider_source<<"\t" << info.doc_len <<endl;
    cout << " doc_len:" << info.doc_len << endl;
    #endif
    //增加其他feature，比如公式数据抽取、质量答案等
}

std::map<long, DocumentInfo>& Indexer::get_docs_info() {
    return _docs_info;
}

DocumentInfo* Indexer::get_doc_info(long docid) {
    std::map<long, DocumentInfo>::iterator iter = _docs_info.find(docid);
    if (iter == _docs_info.end()) {
        return NULL;
    }
    return &(iter->second);
}
void Indexer::load_document_info(char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        cerr << "load document_info error:" << path << endl; 
    }
    while (!feof(file)) {
        fgets(_buffer, BUFFER_SIZE, file);
        string buffer_str(_buffer);
        vector<string> vec;
        explode(buffer_str, "\t", vec); 
        DocumentInfo info;
        long doc_id = string_to_num<long>(vec[0]);
        //info.subject = string_to_num<int>(vec[1]);
        //info.spider_source = string_to_num<int>(vec[2]);
        info.doc_len = string_to_num<int>(vec[1]);
        _docs_info.insert(std::pair<long, DocumentInfo>(doc_id, info));
    }

    fclose(file);
}


//输出meta数据
void Indexer::output_metainfo(char* data_path) {
    char output_name[FILE_NAME_SIZE];
    get_file_name(data_path, META, output_name, FILE_NAME_SIZE);
    FILE * doc_file = fopen(output_name, "w");
    string str_line = num_to_string<int>(_average_length) + '\t' + num_to_string<int>(_total_doc_num);
    fputs(str_line.c_str(), doc_file);
    fclose(doc_file);
}

void Indexer::load_metainfo(char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        cerr << "open raw file to build metainfo error:" << path << endl; 
        return;
    }
    size_t SIZE = 128;
    char buffer[SIZE];
    fgets(buffer, SIZE, file);
    string buffer_str(buffer);
    vector<string> vec;
    explode(buffer_str, "\t", vec); 
    _average_length = string_to_num<int>(vec[0]);
    _total_doc_num = string_to_num<int>(vec[1]);
    #ifdef DEBUG
        cout << "loadmetainfo:" << path << endl;
        cout << "average_length:" << _average_length << " total_doc_num:" << _total_doc_num << endl;
    #endif
    fclose(file);
}

// 载入term信息和term对应倒排meta数据
// 格式:term df term_id file_index offset_begin offset_end
void Indexer::load_worddict(char* path) {
    //_pword_dict->load_dict(path);
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
        if (buffer_vec.size() > 6) {
            info.upper_bound = string_to_num<double>(buffer_vec[6]);
        }
        #ifdef DEBUG
            //printf("term:%s\tdf:%u\tid:%u\tfidx:%u\toff_begin:%ld\toff_end:%ld\n", const_cast<char*>(token.c_str()), info.df, info.dict_id, info.file_index, info.offset_begin, info.offset_end);
        #endif 
        _dict_map.insert(std::pair<string,DictInfo>(token,info) );
        if (info.file_index > 0) {
            InvertedTerm item(info.file_index, info.df, info.offset_begin, info.offset_end);
            //_inverted_index.insert(std::pair<long, InvertedTerm>(info.dict_id, item));
            add_inverted_term(info.dict_id, item);
        }
    }   
    fclose(file);
}

void Indexer::output_worddict(char* path) {
    //_pword_dict->output_dict(path);
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
        snprintf(buffer, SIZE, "%s\t%u\t%u\t%u\t%ld\t%ld\t%lf\n", const_cast<char*>(word.c_str()), info.df, info.dict_id, info.file_index, info.offset_begin, info.offset_end, info.upper_bound);
        fputs(buffer,file);
        ++iter;
    }   
    fclose(file);
}

DictInfo* Indexer::get_word_info(std::string token) {
    map<string,DictInfo>::iterator it = _dict_map.find(token);
    if(it!= _dict_map.end()){
        return &(it->second);
    }
    return NULL;
    //return _pword_dict->get_word_info(token);
}

//从hadoop产出index中建立词典信息和倒排文件
// 记录term idf等信息词典放置在index目录下
void Indexer::build_inverted_index_from_file(char* data_file, char* index_path, char* output_path){
    FILE * file = fopen(data_file, "r");
    if(NULL == file){
        cerr << "open raw file to build invert_index error" << endl; 
        return;
    } 

    unsigned int file_index = 1;
    char file_name[FILE_NAME_SIZE];
    get_file_name(output_path, INDEX, file_name, FILE_NAME_SIZE, file_index);
    FILE *indexfile = fopen(file_name, "w");
    if(NULL == indexfile) {
        cerr << "open file to write index error [" << file_name << "]" << endl;
    }
    //加载已筛选过滤的词典
    get_file_name(index_path, DICT, file_name, FILE_NAME_SIZE);
    load_worddict(file_name);
    char* pch = NULL;
    char* pch_last = NULL;
    DictInfo* term_info = NULL;
    long pos = -1;
    bool new_line = true;

    #ifdef DEBUG 
    char* tmp_buffer = new char[102400];
    string token;
    #endif
    int line_count = 0;
    while (!feof(file)) {
        fgets(_buffer, BUFFER_SIZE, file);
        #ifdef DEBUG
        cout << "input_buffer:" << _buffer << endl;
        #endif
        bool index_head = false;
        //查找token
        if (new_line) {

            cout << "loop_count:" << line_count << endl;
            line_count++;
            pch = strchr(_buffer, '\t');        

            if (pch == NULL){
                cout << "no tab:" << line_count << endl;
                continue;
            }
            //查找term
            string find_token(_buffer, pch - _buffer);
            term_info = get_word_info(find_token); 
            if (term_info == NULL) {
                cout << "word not in dict:" << line_count << endl;
                continue;
            }
            pch++;
            index_head = true;
            #ifdef DEBUG
            token = find_token;
            #endif
        } else {
            pch = _buffer;
        }
        
        //查找换行符，判断倒排读取是否完毕
        pch_last = strrchr(_buffer, '\n');
        if (pch_last == NULL) {
            pch_last = strrchr(_buffer, '\r');
        }
        // term对应倒排未读完
        if (pch_last == NULL) {
            pch_last = _buffer + BUFFER_SIZE - 1;
            long int pos_ahead = 0;
            while (*pch_last != '|' && pch_last > _buffer) {
                pos_ahead--;
                pch_last--;
            }
            fseek(file, pos_ahead, SEEK_CUR);
            new_line = false;

        } else {
            //已读完单个term index
            new_line = true;
        }

        if (pch_last == NULL || pch_last < pch) {
            cout << "pch is NULL or pch_last < pch line_cnt:" << line_count << endl;
            new_line = true;
            continue;
        }

        //输入到index文件中
        if (index_head) {
            pos = ftell(indexfile);
            term_info->file_index = file_index;
            term_info->offset_begin = pos;
            #ifdef DEBUG 
            cout << token << " file_offset_begin:" << pos << endl;
            #endif
        }
        fwrite((void*)pch, sizeof(char), pch_last - pch + 1, indexfile);
        pos = ftell(indexfile);
        term_info->offset_end = pos;

        //for debug
        #ifdef DEBUG 
        strncpy(tmp_buffer, pch, pch_last - pch + 1);
        tmp_buffer[pch_last - pch + 1] = '\0';
        cout << "write_std:" << tmp_buffer << endl;
        int tmp_size = pch_last - pch + 1;
        cout << token << " file_offset_end:" << pos << " len:" << tmp_size << endl;
        #endif
    }
    #ifdef DEBUG
        delete tmp_buffer;
    #endif
    fclose(file);
    fclose(indexfile);
    output_worddict(file_name);
    cout<<"end to loop"<<endl;
}
//除倒排索引外的其他所有元数据
void Indexer::load_index_meta_data(char* path) {
    strncpy(_data_path, path, strlen(path));
    char file_name[FILE_NAME_SIZE];
    get_file_name(path, DICT, file_name, FILE_NAME_SIZE);
    load_worddict(file_name);
    //  暂时没有brief数据
    get_file_name(path, DOC, file_name, FILE_NAME_SIZE);
    load_document_info(file_name);

    get_file_name(path, META, file_name, FILE_NAME_SIZE);
    load_metainfo(file_name);

}
FILE* Indexer::get_index_file(unsigned int file_index) {
    std::map<unsigned int, FILE*>::iterator iter = _file_handles.find(file_index);
    if (iter != _file_handles.end()) {
        return iter->second;
    }
    char file_name[FILE_NAME_SIZE];
    get_file_name(_data_path, INDEX, file_name, FILE_NAME_SIZE, file_index);
    FILE* index_file = fopen(file_name, "r");
    if (index_file == NULL) {
        cout << "open index file to read error " << file_name << endl;
        return NULL;
    }
    _file_handles.insert(std::pair<unsigned int, FILE*>(file_index, index_file));
    return index_file;
}

std::vector<InvertedPosting>& Indexer::get_inverted_posting_list() {
    return _inverted_posting_list;
}

int Indexer::load_term_index(size_t term_id) {
    InvertedTerm* info = get_inverted_term(term_id);
    return load_term_index(info);
}
int Indexer::load_term_index(InvertedTerm* info) {
    if (info == NULL || info->file_index == 0) {
        cout << "terminfo is null or fileindex:" << info->file_index  << endl;
        return -1;
    }
    if (info->load_type == COMPLETE_LOAD) {
        return info->pos_end - info->pos_begin;
    }
    FILE* index_file = get_index_file(info->file_index);
    fseek(index_file, info->offset_begin, SEEK_SET);
    int left_length = info->offset_end - info->offset_begin;
    info->pos_begin = _inverted_posting_list.size();
    char* save_ptr = NULL;
    vector<string> vec;
    size_t to_read = -1;
    #ifdef TRACE
    long tmp_pos = 0;
    cout << "begin_load_term  size:" << info->pos_begin << endl;
    cout << "offset_begin:" << info->offset_begin << "offset_end:" << info->offset_end << endl;
    #endif

    while (true) {

        #ifdef TRACE
        tmp_pos = ftell(index_file);
        cout << "before read pos:" << tmp_pos << endl;
        #endif
        to_read = (READ_SIZE - 1) <= left_length ? (READ_SIZE - 1) : left_length;
        size_t nread = fread(_buffer, sizeof(char), to_read, index_file); 
        if (nread == 0) {
            break;
        }

        //未读完调整位置
        if (left_length - nread != 0) {
            char* pch_last = _buffer + nread - 1;
            int pos_ahead = 0;
            while (*pch_last != '|' && pch_last > _buffer) {
                pch_last--;
                pos_ahead--;
            }
            if (*pch_last == '|') {
                fseek(index_file, pos_ahead, SEEK_CUR);
                *pch_last = '\0';
                nread += pos_ahead;
            }
        } else {
            //fread不会自动添加'\0'
            char* pch_last = _buffer + nread;
            *pch_last = '\0';
        }

        #ifdef TRACE
         //cout << "buffer:" << _buffer << endl;
        #endif
        char* ptr = strtok_r(_buffer, "|", &save_ptr);
        while (ptr != NULL) {
            string str(ptr);
            explode(str, "#", vec);
            #ifdef TRACE
                cout << str << endl;
            #endif
            if (vec.size() != 2) {
                cout << "error posting item size:" << vec.size() << " str:" << str << endl; 
                ptr = strtok_r(NULL, "|", &save_ptr);
                continue;
            }
            InvertedPosting post;
            post.doc_id = string_to_num<long>(vec[0]);
            post.tf = string_to_num<size_t>(vec[1]);
            _inverted_posting_list.push_back(post);
            ptr = strtok_r(NULL, "|", &save_ptr);
        }

        left_length -= nread;

        #ifdef TRACE
        tmp_pos = ftell(index_file);
        cout << "after read pos:" << tmp_pos << " read_len:" << nread  << " left_len:" << left_length << endl;
        #endif

        if (left_length <= 0) {
            break;
        }
    } 
    info->offset_cur = ftell(index_file);
    info->pos_end = _inverted_posting_list.size();
    info->load_type = COMPLETE_LOAD;
    #ifdef DEBUG
    int tmp_size = info->pos_end - info->pos_begin;
    cout << "end_load_term size:" << tmp_size << " total_size:" <<  info->pos_end <<endl;
    #endif
    return info->pos_end - info->pos_begin;
}
//load词典中所有词的倒排到内存中
void Indexer::load_inverted_index() {
    std::map<size_t, size_t>::iterator iter = _inverted_index.begin();
    while (iter != _inverted_index.end()) {
        InvertedTerm* item = &_inverted_term_list[iter->second];
        if (item->file_index > 0) {
            load_term_index(item);
            //load_term_index(2);
            //break;
        }
        iter++;
    } 
}
size_t Indexer::add_inverted_term(const size_t& term_id, const InvertedTerm& item) {
    std::map<size_t, size_t>::iterator iter = _inverted_index.find(term_id);
    if (iter == _inverted_index.end()) {
        _inverted_term_list.push_back(item);
        size_t index = (size_t)(_inverted_term_list.size() - 1);
        _inverted_index.insert(std::pair<size_t, size_t>(term_id, index));
        return index;
    }
    return iter->second;
}

//成功取得下一个文档则返回true,否则为false
//获取ID>= doc_id的文档信息
bool Indexer::get_next_doc(size_t inverted_term_index, long doc_id, int& pos_cur, DocumentItem& item) {
    InvertedTerm* word_item = &_inverted_term_list[inverted_term_index];

    if (word_item == NULL) {
        cerr << " inverted_term_info is NULL:" << endl;
        return false;
    }
    if (word_item->load_type == NOT_LOAD) {
        load_term_index(word_item);
    }
    if (pos_cur < 0) {
        pos_cur = word_item->pos_begin;
    }
    while (pos_cur < word_item->pos_end) {
        const InvertedPosting& post_item = _inverted_posting_list[pos_cur];
        if (post_item.doc_id < doc_id) {
            pos_cur++;
        } else {
            item.doc_id = post_item.doc_id;
            item.tf = post_item.tf;
            break;
        }
    }

    if (pos_cur == word_item->pos_end) {
        return false;
    }
    return true;
}

int Indexer::get_doc_length(long docid) {
    int ret_len = _average_length;
    DocumentInfo* info = get_doc_info(docid);
    if (info != NULL) {
        ret_len = info->doc_len;
    }
    return ret_len;
}

int Indexer::get_total_doc_num(){
    return _total_doc_num;
}

int Indexer::get_average_length(){
    return _average_length;
}

char* Indexer::get_index_path() {
    return _data_path;
}

//根据文件类型,返回对应文件名
void Indexer::get_file_name(const char* path, NAME_TYPE type, char* output_name, size_t output_name_size, int file_index) {
    memset(output_name, 0, output_name_size);
    char* file_name = const_cast<char*>(PATH_NAME[type]);
    if (type == INDEX) {
        snprintf(output_name, output_name_size, "%s/%s_%d", path, file_name, file_index);
    } else {
        snprintf(output_name, output_name_size, "%s/%s", path, file_name);
    }
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
