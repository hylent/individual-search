/***************************************************************************
 * 
 * Copyright (c) 2016, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file ../process/Rank.cpp
 * @author caolin
 * @date 2016/06/16 15:22:15
 * @brief 
 *  
 **/
#include "rank.h"
#include "data.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm> 
#include <climits>
using std::string;
using std::vector;
using std::cout;
//定义返回结果文档数
#define RESULT_SIZE 200
using std::endl;
namespace cute_engine{
//#define DEBUG

Collector::Collector(Indexer* inpar) : _indexer(inpar) {
    _word_id = -1;
    _tf = -1;
    _pos_cur = -1;
    _upper_bound = 0.0;
//    _idf = 0.0;
    _inverted_term_index = -1;
}

Collector::~Collector() {
}

//遍历倒排取下一个文档，成功则返回true,遍历结束则返回false
bool Collector::next() {
    return _indexer->get_next_doc(_inverted_term_index, _item.doc_id + 1, _pos_cur, _item);
} 
int Collector::get_word_id() {
   return _word_id;
}
long Collector::get_doc_id() {
    return _item.doc_id;
}
int Collector::get_query_tf(){
    return _tf;
}
double Collector::get_query_idf(){
    return _idf;
}
int Collector::get_query_doc_tf(){
    return _item.tf;
}
int Collector::get_doc_length(){
    return _indexer->get_doc_length(_item.doc_id);
}

long Collector::get_next_doc(long doc_id) { 
    bool has_next = _indexer->get_next_doc(_inverted_term_index, doc_id, _pos_cur, _item); 
    if (has_next == false) { 
        _item.doc_id = LONG_MAX;
    } 
    return _item.doc_id;
} 
int Collector::get_average_length() { 
    return _indexer->get_average_length(); 
} 
double Collector::get_upper_bound() {
    return _upper_bound;
}
Rank::Rank() {
}

Rank::~Rank(){
}

void Rank::rank_docs(){
}

long Rank::get_next_doc(long doc_id) {
    //return -1;
    return LONG_MAX;
}

Rank::Rank(const std::vector<Collector>& invec){
    _collector_vec = invec; 
}

void Rank::set_collector_vec(const std::vector<Collector>& invec) {
    _collector_vec = invec;
}

vector<DocScore> Rank::get_docs_score(){
    return _score_vec;
}

SimRank::SimRank(){
    _cur_doc_id = -1;
}

SimRank::SimRank(std::vector<Collector> invec):Rank(invec){
    _cur_doc_id = -1;
}

SimRank::~SimRank(){
}
//OR查找倒排
long SimRank::get_next_doc(long in_doc_id) {
    unsigned int size = _collector_vec.size();
    if (size == 0) {
        return -1;
    }
    long doc_id = in_doc_id;
    long ret_doc_id = -1;
    //and操作寻找next_doc
    int loop = 0;
    while (NO_OMIT_WORD_NUM > 0) {
        unsigned int i = 0;
        for (i = 0; i < size && i < NO_OMIT_WORD_NUM; i++) {
            ret_doc_id = _collector_vec[i].get_next_doc(doc_id);
            if (ret_doc_id == LONG_MAX) {
                return -1;
            }

            cout << " get_doc[" << loop <<"]" << " try_docid:" << doc_id << " term_[" << i << "]:"<< ret_doc_id << endl;
            loop ++;

            if (ret_doc_id != doc_id) {
                doc_id = ret_doc_id;
                break;
            } 

        }
        if ((i != 0) && (i == size || i == NO_OMIT_WORD_NUM)) {
            break;
        }
    }

    //or操作寻找next_smallest_doc
    long min_doc_id = LONG_MAX;
    for (unsigned int i = NO_OMIT_WORD_NUM; i < size; i++) {
        ret_doc_id = _collector_vec[i].get_next_doc(doc_id);
        if (min_doc_id > ret_doc_id) {
            min_doc_id = ret_doc_id;
        }
    }

    if (NO_OMIT_WORD_NUM > 0) {
        return doc_id;
    } else {
        return min_doc_id;
    }
}
//返回的不是pivot_term_index, 而是pivot_term对应的_collector_index
int SimRank::find_pivot_term(const std::vector<std::pair<int, long> >& posting, double threshod) {
    int nsize = posting.size();
    double upper_bound = 0.0;
    for (int i = 0; i < nsize; i++) {
        int collector_index = posting[i].first; 
        upper_bound += _collector_vec[collector_index].get_upper_bound();
        if (upper_bound >= threshod) {
            return i;
        }
    }
    return -1;
}
//WAN算法查找倒排
//返回pivot_term在_cur_term_posting 中的偏移位置
int SimRank::get_next_doc_wand(double threshold, long& ret_doc_id) {
    //int count = 0;
    while (true) {
        //count ++ ;

        //struct timeval time_start;
        //gettimeofday(&time_start, NULL);
        //sort(_cur_term_posting.begin(), _cur_term_posting.end(), SimRank::posting_sort);

        //get_time_space(time_start, " sort_list ");

        #ifdef TRACE
        cout << " after sort term_posting threshold:" << threshold << endl;
        for (unsigned int i = 0; i < _cur_term_posting.size(); i++){
            int index = _cur_term_posting[i].first;
            cout << " i:" << i << " index:" << _cur_term_posting[i].first << " docid:" << _cur_term_posting[i].second << " bound:"<< _collector_vec[index].get_upper_bound() << endl;
        } 
        #endif

        //gettimeofday(&time_start, NULL);
        int posting_index = find_pivot_term(_cur_term_posting, threshold);
        //get_time_space(time_start, " find_pivot_term ");
        //未找到
        if (posting_index == -1) {
            return -1;
        }
        //在_collector_vec 中的偏移位置
        //int pivot_term_index = _cur_term_posting[posting_index].first;
        long pivot_doc_id = _cur_term_posting[posting_index].second;
        #ifdef TRACE
        cout << " post_index:" << posting_index << " pivot_idx:" << _cur_term_posting[posting_index].first << " pivot_docid:" << pivot_doc_id << " cur_docid" << _cur_doc_id << endl;
        #endif
        if (pivot_doc_id == LONG_MAX) {
            return -1;
        }
        if (pivot_doc_id <= _cur_doc_id) {
            //or just select one term to advance index
            //gettimeofday(&time_start, NULL);
            /*
            for (int i = 0; i <=  posting_index; ) { 
                int collector_index = _cur_term_posting[i].first;
                long ret_doc_id = _collector_vec[collector_index].get_next_doc(_cur_doc_id + 1); 
                if (ret_doc_id < LONG_MAX) {
                    _cur_term_posting[i].second = ret_doc_id;
                    i++;
                } else {
                    _cur_term_posting.erase(_cur_term_posting.begin() + i); 
                }
            }  */
            
            int idx = advance_term(posting_index, _cur_doc_id + 1);
            insert_sort(idx); 
            //get_time_space(time_start, " loop_inverted_index1 ");
        } else {
            if (_cur_term_posting[0].second == pivot_doc_id) {
                _cur_doc_id = pivot_doc_id;
                ret_doc_id = pivot_doc_id;
                return posting_index; 
            } else {

                //gettimeofday(&time_start, NULL);
               /* 
                for (int i = 0; i < posting_index; ) {
                    int collector_index = _cur_term_posting[i].first;
                    long ret_doc_id = _collector_vec[collector_index].get_next_doc(pivot_doc_id); 
                    if (ret_doc_id < LONG_MAX) {
                        _cur_term_posting[i].second = ret_doc_id;
                        i++;
                    } else {
                        _cur_term_posting.erase(_cur_term_posting.begin() + i); 
                    }
                } */ 
                int idx = advance_term(posting_index - 1, pivot_doc_id);
                insert_sort(idx);
                //get_time_space(time_start, " loop_inverted_index2 ");
            }
        }

    }
}

void SimRank::insert_sort(int index) {
    /*
        cout << " before insert_sort index:" << index << endl;
        for (unsigned int i = 0; i < _cur_term_posting.size(); i++){
            int index = _cur_term_posting[i].first;
            cout << " i:" << i << " index:" << _cur_term_posting[i].first << " docid:" << _cur_term_posting[i].second << " bound:"<< _collector_vec[index].get_upper_bound() << endl;
        }  */
    int size = _cur_term_posting.size();
    std::pair<int, long>  index_item = _cur_term_posting[index];
    int i = 0;
    for (; i < size; i++) {
        if (_cur_term_posting[i].second >= index_item.second && i != index) {
            break;
        } 
    }
        //cout << " insert_sort inset_pos:" << i << endl;
    if (i < index) {
        for (int j = index; j > i; j--) {
            _cur_term_posting[j] = _cur_term_posting[j - 1];
        }
        _cur_term_posting[i] = index_item;
    } else if (i > index){
        for (int j = index; j < i - 1; j++) {
            _cur_term_posting[j] = _cur_term_posting[j + 1];
        }
        _cur_term_posting[i - 1] = index_item;
    }
        /*
        cout << " after insert_sort" << endl;
        for (unsigned int i = 0; i < _cur_term_posting.size(); i++){
            int index = _cur_term_posting[i].first;
            cout << " i:" << i << " index:" << _cur_term_posting[i].first << " docid:" << _cur_term_posting[i].second << " bound:"<< _collector_vec[index].get_upper_bound() << endl;
        }  */
}
// [0...posting_index] 中选择一次，遍历所有到doc_id >= next_doc_id
int SimRank::advance_term(int posting_index, long next_doc_id) {
    double max_idf = 0.0;
    int max_idf_index = -1; 
    for (int i = 0; i <= posting_index; i++) {
        int collector_index = _cur_term_posting[i].first;
        if (_collector_vec[collector_index].get_doc_id() >= next_doc_id) {
            //后面所有文档均满足要求
            break;
        }
        double term_idf = _collector_vec[collector_index].get_query_idf();
        if (term_idf > max_idf) {
            max_idf_index = i;
        }
    }
    int collector_index = _cur_term_posting[max_idf_index].first;

    long ret_doc_id = _collector_vec[collector_index].get_next_doc(next_doc_id); 
    _cur_term_posting[max_idf_index].second = ret_doc_id;
    return max_idf_index;
}

//初始化posting: 所有term对应cur_doc_id
void SimRank::init_term_posting() {

    _cur_term_posting.clear();
    int nsize = _collector_vec.size();
    for (int i = 0; i < nsize; i++) {
        long doc_id = _collector_vec[i].get_next_doc(-1);
        _cur_term_posting.push_back(std::pair<int, long>(i, doc_id));
    }
    sort(_cur_term_posting.begin(), _cur_term_posting.end(), SimRank::posting_sort);
}
/* 原and实现方法
void SimRank::rank_docs() {
    _score_vec.clear();
    long doc_id = -1;
    //遍历倒排列表
    while (true) {
        doc_id = get_next_doc(doc_id);
        if (doc_id <= 0) {
            break;
        }
        sort(_collector_vec.begin() + NO_OMIT_WORD_NUM, _collector_vec.end(), Rank::collector_sort);
        //计算不同词对该文档的打分值，并求和
        std::vector<Collector>::iterator collector_iter = _collector_vec.begin();
        while(collector_iter != _collector_vec.end() && collector_iter->get_doc_id() == doc_id) {
            double tmp_score = get_score(*collector_iter);
            score += tmp_score;

            #ifdef DEBUG
                int word_id = collector_iter->get_word_id();
                cout << "docid:" << doc_id << " wordid:" << word_id << " cons:" << tmp_score << endl ;
            #endif
            //该word_id对应倒排遍历下一个文档
            bool has_next = (*collector_iter).next();
            if (has_next) {
                //遍历下一个word_id指向的倒排
                ++collector_iter;
            } else {
                //如果该word_id对应倒排已经遍历完毕，则删除
                collector_iter = _collector_vec.erase(collector_iter);
            }
        }

            #ifdef DEBUG
                cout << "score_caculate doc_id:" << doc_id << " end_score:" << score << endl; 
            #endif

        //将文档打分与目前选中文档打分比较，判断是否选入
        DocScore doc_score;
        doc_score.doc_id = doc_id;
        doc_score.doc_score = score;
        if(_score_vec.size() < RESULT_SIZE){
            //std::make_heap(_score_vec.begin(),_score_vec.end(),Rank::score_sort);
            _score_vec.push_back(doc_score); 
            std::push_heap(_score_vec.begin(), _score_vec.end(), Rank::score_sort);
        } else {
            //当前计算文档比目前计算结果文档打分更高，需要选入
            if(_score_vec.front().doc_score < score){
                std::pop_heap(_score_vec.begin(),_score_vec.end(),Rank::score_sort);
                _score_vec.pop_back();
                _score_vec.push_back(doc_score); 
                std::push_heap(_score_vec.begin(),_score_vec.end(),Rank::score_sort);
            }
        }
        doc_id++;
    }
} */

void SimRank::set_query_str(const string& str) {
    _query_str = str;
}

void SimRank::precise_rank_docs() {
    int nsize = _score_vec.size();
    const int BUFFER_LEN = 64;
    char doc_id_buffer[BUFFER_LEN];
    vector<std::pair<int, int> > query_tokens_len;
    int selected_query_len = get_string_token_len(_query_str, query_tokens_len);
    vector<std::pair<int, int> > doc_tokens_len;
    for (int i = 0; i < nsize; i++) {
        DocScore& doc_score = _score_vec[i];
        snprintf(doc_id_buffer, BUFFER_LEN, "%ld", doc_score.doc_id);
        string doc_id_key(doc_id_buffer);
        string doc_str;
        leveldb::Status s = _forward_db->Get(leveldb::ReadOptions(), doc_id_key, &doc_str);
        if (!s.ok()) { 
            doc_score.precise_score = -1;
            continue;
        }
        int selected_doc_len = get_string_token_len(doc_str, doc_tokens_len);
        string ret = longest_common_string(_query_str, doc_str, query_tokens_len, doc_tokens_len);
        int common_len = ret.length();
        #ifdef DEBUG
        cout << "selected_query_len:" << selected_query_len << " doc_id:" << doc_id_key << " selected_doc_len:" << selected_doc_len << " comm_len:" << common_len << endl;
        #endif
        doc_score.precise_score = (float)(common_len) / (selected_query_len + selected_doc_len) * 2;
    }
}

void SimRank::set_forward_db(leveldb::DB* in_db) {
    _forward_db = in_db;
}

string SimRank::longest_common_string(const string& str1, const string& str2, 
                            const vector<std::pair<int, int> >& tokens_len1, 
                            const vector<std::pair<int, int> >& tokens_len2) {
    int tokens_size_one = tokens_len1.size();
    int tokens_size_two = tokens_len2.size();
    if (tokens_size_one <= 0 || tokens_size_two <=0 ) {
        return "";
    }

    //记录位置从1开始
    for (int i = 0; i <= tokens_size_one; i++) {
        _strlen[i][0] = 0;
    }
    for (int j = 0; j <= tokens_size_two; j++) {
        _strlen[0][j] = 0;
    }
    //计算最长公共字长度
    //int common_str_len = 0;
    //注意tokens_len存储字符信息从0开始，其他数组_strlen, _path均从1开始
    for (int j = 1; j <= tokens_size_two; j++) {
        for (int i = 1; i <= tokens_size_one; i++) {
            if (compare_token(str1, str2, tokens_len1[i - 1], tokens_len2[j - 1])) {
                _strlen[i][j] = _strlen[i - 1][j - 1] + 1;
                _path[i][j] = 0;
            } else if (_strlen[i - 1][j] > _strlen[i][j - 1]) {
                //取往上的路径
                _strlen[i][j] = _strlen[i - 1][j];
                _path[i][j] = 1;
            } else {
                //取往左的路径
                _strlen[i][j] = _strlen[i][j - 1];
                _path[i][j] = -1;
            }
        }
    }
    //回溯记录公共字串
    string ret = "";
    int row = tokens_size_one;
    int col = tokens_size_two;
    while (row > 0 && col > 0) {
        if (_path[row][col] == 0) {
            int pos = tokens_len1[row - 1].first;
            int len = tokens_len1[row - 1].second;
            string tmp(str1, pos, len);
            ret = tmp + ret;    
            row -= 1;
            col -= 1;
        } else if (_path[row][col] == 1) {
            row -= 1;
        } else {
            col -= 1;
        }
    }
    return ret;
}

bool SimRank::compare_token(const string& str1, const string& str2, const std::pair<int, int>& pair1, const std::pair<int, int>& pair2) {
    if (pair1.second != pair2.second) {
        return false;
    }
    int pos1 = pair1.first;
    int pos2 = pair2.first;
    int len = pair1.second;
    
    //int str1_len = str1.length();
    //int str2_len = str2.length();
    //cout << " str1:" << str1 << " pos:" << pair1.first << " len:" << pair1.second << " strlen:" << str1_len << endl;
    //cout << " str1:" << str1 << " pos:" << pair1.first << " len:" << pair1.second << " strlen:" << str2_len <<  endl;
    for(int i = 0; i < len; i++) {
        if (str1[pos1 + i] != str2[pos2 + i]) {
            return false;
        }
    }
    return true;
}

int SimRank::get_string_token_len(const string& str, vector<std::pair<int, int> >& token_len) {
    int len = str.length();
    token_len.clear();
    int i = 0;
    for (i = 0; i < len; ) {
        int bytes = 0;
        unsigned char chr = str[i];
        if (chr < 0x80) {
            bytes = 1;
        } else if (chr >= 0xC0 && chr < 0xE0) {
            bytes = 2;
        } else if(chr >= 0xE0 && chr < 0xF0) {
            bytes = 3;
        } else if(chr >= 0xF0 && chr < 0xF8) {
            bytes = 4;
        } else if(chr >= 0xF8 && chr < 0xFC) {
            bytes = 5;
        } else if (chr >= 0xFC && chr <= 0xFD) {
            bytes = 6;
        } else {
            bytes = 1;
        }

        // 存储单个字符的pos和长度
        token_len.push_back(std::pair<int, int>(i, bytes)); 
        i += bytes;
        //太长则截断
        if (token_len.size() >= (MAX_QUERY_WORD_LENGTH - 1)) {
            break; 
        }
    }
    #ifdef DEBUG
    cout << endl;
    cout << "str:" << str << " len:" << i << endl;
    for (unsigned int i = 0; i < token_len.size(); i++) {
        cout << token_len[i] << " "; 
    }
    cout << endl;
    #endif 
    //返回最终选用的文本长度
    return i;
}

void SimRank::rank_docs() {
    _score_vec.clear();
    init_term_posting();
    _cur_doc_id = -1;
    //遍历倒排列表
    double threshod = 0.0;
    long doc_id;
    int count = 0;   //for debug 统计计算文档数量

    //struct timeval time_start, caculate_time_start;
    while (true) {
        count ++;

        //gettimeofday(&time_start, NULL);
        int posting_index = get_next_doc_wand(threshod, doc_id);
        //get_time_space(time_start, " get_next_doc ");

        if (posting_index < 0) {
            break;
        }

        //gettimeofday(&caculate_time_start, NULL);
        //计算不同词对该文档的打分值，并求和
        double score = 0.0;
        int posting_size = _cur_term_posting.size();
        for (int i = 0; i <= posting_size; i++) {
            if (_cur_term_posting[i].second != doc_id) {
                break;
            }
            int collector_index = _cur_term_posting[i].first;
            double tmp_score = get_score(_collector_vec[collector_index]);
            score += tmp_score;
            #ifdef TRACE
                int word_id = _collector_vec[collector_index].get_word_id();
                cout << "docid:" << doc_id << " wordid:" << word_id << " cons:" << tmp_score << endl ;
            #endif
        }

        #ifdef TRACE
            cout << "score_caculate doc_id:" << doc_id << " end_score:" << score << endl; 
        #endif

        //将文档打分与目前选中文档打分比较，判断是否选入
        DocScore doc_score;
        doc_score.doc_id = doc_id;
        doc_score.doc_score = score;
        if(_score_vec.size() < RESULT_SIZE){
            //std::make_heap(_score_vec.begin(),_score_vec.end(),Rank::score_sort);
            _score_vec.push_back(doc_score); 
            std::push_heap(_score_vec.begin(), _score_vec.end(), Rank::score_sort);
        } else {
            //当前计算文档比目前计算结果文档打分更高，需要选入
            if(_score_vec.front().doc_score < score){
                std::pop_heap(_score_vec.begin(),_score_vec.end(),Rank::score_sort);
                _score_vec.pop_back();
                _score_vec.push_back(doc_score); 
                std::push_heap(_score_vec.begin(),_score_vec.end(),Rank::score_sort);
            }
        }
        threshod = _score_vec.front().doc_score;

        //get_time_space(caculate_time_start, " caculate_time ");
    }
    cout << "\tcount:" << count;
}

double SimRank::get_score(Collector& collector){
    //bm25计算当前文档分值
    double idf = collector.get_query_idf();
    int tf = collector.get_query_doc_tf();
    double average_len = collector.get_average_length();
    double doc_len = collector.get_doc_length();
    double score = idf * ( tf * (1.5 + 1) ) / ( tf + 1.5 * ( 1 - 0.75 + 0.75 * doc_len/average_len));
    #ifdef TRACE
        cout << "id:" << collector.get_word_id() << " tf:" << tf << " idf:" << idf <<  " doclen:" << doc_len << " average_len:" << average_len << " score:" << score << endl; 
    #endif
    return score;
}

bool SimRank::posting_sort(const std::pair<int, long>&a, const std::pair<int, long>& b) {
    return a.second < b.second;
}


bool Rank::collector_sort(Collector& a, Collector& b){
    return a.get_doc_id() < b.get_doc_id();
}

//建立最小堆，如果a.doc_score < b.doc_score则为最大堆
bool Rank::score_sort(const DocScore& a, const DocScore& b){
    return a.doc_score > b.doc_score;
}

bool Rank::precise_score_sort(const DocScore& a, const DocScore& b){
    return a.precise_score > b.precise_score;
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
