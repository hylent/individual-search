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
using std::string;
using std::vector;
using std::cout;
//定义返回结果文档数
#define RESULT_SIZE 10
using std::endl;

namespace cute_engine{

Collector::Collector(Indexer* inpar) : _indexer(inpar) {
    _word_id = -1;
    _item.doc_id = -1;
    _tf = -1;
    _idf = 0.0;
}

Collector::~Collector() {}

//遍历倒排取下一个文档，成功则返回true,遍历结束则返回false
bool Collector::next() {
    return _indexer->get_next_doc(_word_id, _item.doc_id + 1, _item);
} 
int Collector::get_word_id() {
   return _word_id;
}
int Collector::get_doc_id() {
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
    bool has_next = _indexer->get_next_doc(_word_id, doc_id, _item);
    if (has_next) {
        return _item.doc_id;
    } else {
        return -1;
    }
}

int Collector::get_average_length(){
    return _indexer->get_average_length();
}

Rank::Rank(){
}

Rank::~Rank(){
}

void Rank::rank_docs(){
}

long Rank::get_next_doc(long doc_id) {
    return -1;
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

}

SimRank::SimRank(std::vector<Collector> invec):Rank(invec){

}

SimRank::~SimRank(){
}

//OR查找倒排
long SimRank::get_next_doc(long in_doc_id) {
    int size = _collector_vec.size();
    if (size == 0) {
        return -1;
    }
    long doc_id = in_doc_id;
    while (true) {
        for (int i = 0; i < size; i++) {
            _collector_vec[i].get_next_doc(doc_id);
            
        }
    }
    for (int i = ; i < size; i++) {
        _collector_vec[i].get_next_doc(doc_id);
        
    }
}

//根据must_word  AND查找倒排
long SimRank::get_next_doc(long in_doc_id) {
    int size = _collector_vec.size();
    if (size == 0) {
        return -1;
    }
    if (size == 1) {
        return _collector_vec[0].get_next_doc(in_doc_id);
    }
    long doc_id = in_doc_id;
    long tmp_doc_id = -1;
    while (true) {
        doc_id = _collector_vec[0].get_next_doc(doc_id);
        if (doc_id == -1) {
            return doc_id;
        }
        tmp_doc_id = _collector_vec[1].get_next_doc(doc_id);
        if (tmp_doc_id == -1) {
            return tmp_doc_id;
        }

        if (tmp_doc_id == doc_id) {
            break;
        } else {
            doc_id = tmp_doc_id; 
        }
    }
    //其他term遍历到大于或等于doc_id的位置
    for (int i = 2; i < size; i++) {
        _collector_vec[i].get_next_doc(doc_id);
    }
    return doc_id;
}
void SimRank::rank_docs(){
    _score_vec.clear();
    long doc_id = -1;
    doc_id = get_next_doc(doc_id);
    #ifdef DEBUG
        cout << " get_next_doc_id:" << doc_id << endl;
    #endif
    //遍历倒排列表
    while (doc_id > 0) {
        double score = 0.0;
        if (_collector_vec.size() > NO_OMIT_WORD_NUM) {
            //? 是否work，会不会前几个term也变化了
            sort(_collector_vec.begin() + NO_OMIT_WORD_NUM, _collector_vec.end(), Rank::collector_sort);
        }
        //计算不同词对该文档的打分值，并求和
        std::vector<Collector>::iterator collector_iter = _collector_vec.begin();
        while(collector_iter != _collector_vec.end() && collector_iter->get_doc_id() == doc_id) {
            double tmp_score = get_score(*collector_iter);
            score += tmp_score;
            /*
            #ifdef DEBUG
                int word_id = collector_iter->get_word_id();
                cout<<word_id<<" cons:"<<tmp_score<<" ";
            #endif
            */
            //该word_id对应倒排遍历下一个文档
            bool has_next = (*collector_iter).next();
            if (has_next) {
                //遍历下一个word_id指向的倒排
                ++collector_iter;
            } else {
                #ifdef DEBUG
                    cout<<"erase word_id iter:"<<collector_iter->get_word_id()<<endl;
                    cout<<"collector size:"<<_collector_vec.size()<<endl;

                #endif
                //如果该word_id对应倒排已经遍历完毕，则删除
                collector_iter = _collector_vec.erase(collector_iter);
            }
        }

            #ifdef DEBUG
                cout << " end caculate doc_id:" << doc_id << " end_score:" << score << endl; 
            #endif

        //将文档打分与目前选中文档打分比较，判断是否选入
        DocScore doc_score;
        doc_score.doc_id = doc_id;
        doc_score.doc_score = score;
        if(_score_vec.size() < RESULT_SIZE){
            _score_vec.push_back(doc_score);
            if(_score_vec.size() == RESULT_SIZE){
                std::make_heap(_score_vec.begin(),_score_vec.end(),Rank::score_sort);
                #ifdef DEBUG
                cout<<"after make heap"<<endl;
                cout<<_score_vec[0].doc_score<<endl;
                cout<<_score_vec[1].doc_score<<endl;
                cout<<_score_vec[2].doc_score<<endl;
                cout<<endl;
                #endif
            }
        }else{
            //当前计算文档比目前计算结果文档打分更高，需要选入
            if(_score_vec.front().doc_score < score){
                
                std::pop_heap(_score_vec.begin(),_score_vec.end(),Rank::score_sort);
                _score_vec.pop_back();
                _score_vec.push_back(doc_score); 
                std::push_heap(_score_vec.begin(),_score_vec.end(),Rank::score_sort);
            }
        }
        doc_id++;
        doc_id = get_next_doc(doc_id);
        #ifdef DEBUG
            cout << " get_next_doc_id:" << doc_id << endl;
        #endif
    }
}

double SimRank::get_score(Collector& collector){
    //bm25计算当前文档分值
    double idf = collector.get_query_idf();
    int tf = collector.get_query_doc_tf();
    double average_len = collector.get_average_length();
    double doc_len = collector.get_doc_length();
    double score = idf * ( tf * (1.5 + 1) ) / ( tf + 1.5 * ( 1 - 0.75 + 0.75 * doc_len/average_len));
    #ifdef DEBUG
        cout << "id:" << collector.get_word_id() << " tf:" << tf << " idf:" << idf << " score:" << score << endl; 
    #endif
    return score;
}

bool Rank::collector_sort(Collector a,Collector b){
    return a.get_doc_id() < b.get_doc_id();
}

//建立最小堆，如果a.doc_score < b.doc_score则为最大堆
bool Rank::score_sort(DocScore a,DocScore b){
    return a.doc_score > b.doc_score;
}

}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
