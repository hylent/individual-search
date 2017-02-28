/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file ../process/Rank.cpp
 * @author caolin01(com@baidu.com)
 * @date 2014/06/16 15:22:15
 * @brief 
 *  
 **/
#include "rank.h"
#include "data.h"
#include<string>
#include<vector>
#include<iostream>
using std::string;
using std::vector;
using std::cout;
//定义返回结果文档数
#define RESULT_SIZE 3
using std::endl;
//#define DEBUG

namespace cute_engine{

    //判断倒排是否遍历结束，否则往后遍历
bool Collector::next(){
    ++_iter;
    if(_iter != _iter_end){
        _doc_id = _iter->doc_id;
        return false;
    }else{
        return true;
    }
}
int Collector::get_word_id(){
    return _word_id;
}
int Collector::get_doc_id(){
    return _iter->doc_id;
}
int Collector::get_query_tf(){
    return _tf;
}
double Collector::get_query_idf(){
    return _idf;
}
int Collector::get_query_doc_tf(){
   // return (*_iter).hits.size();
   return _iter->end - _iter->begin;
}
int Collector::get_doc_length(){
   int doc_id = get_doc_id(); 
   std::map<int,DocumentInfo>::iterator iter = (*_docs_info).find(doc_id);
   if(iter != (*_docs_info).end()){
        return (iter->second).length;
   }else{
        return _average_length;
   }
}

int Collector::get_average_length(){
    return _average_length;
}
Rank::Rank(){
}

Rank::~Rank(){
}

void Rank::rank_docs(){
}

Rank::Rank(std::vector<Collector> invec){
   _collector_vec = invec; 
}

vector<DocScore> Rank::get_docs_score(){
    return _score_vec;
}

SimRank::SimRank(std::vector<Collector> invec):Rank(invec){

}

SimRank::~SimRank(){
}

void SimRank::rank_docs(){
    _score_vec.clear();
   while(_collector_vec.size() > 0){ 
       //按文档ID排序
        sort(_collector_vec.begin(),_collector_vec.end(),Rank::collector_sort);
        std::vector<Collector>::iterator collector_iter = _collector_vec.begin();
        int first_doc_id = collector_iter->get_doc_id();
        #ifdef DEBUG
            cout<<"===="<<endl;
           cout<<first_doc_id<<" begin to rank:"<<endl; 
           if(first_doc_id==0){
                cout<<"doc_id:0 word_id:"<<collector_iter->get_word_id()<<endl;
           }
        #endif
        double score = 0.0;
        //计算不同词对该文档的打分值，并求和
        while(collector_iter != _collector_vec.end() && collector_iter->get_doc_id() == first_doc_id) {
            double tmp_score = get_score(*collector_iter);
            score += tmp_score;
            #ifdef DEBUG
                int word_id = collector_iter->get_word_id();
                cout<<word_id<<" cons:"<<tmp_score<<" ";
            #endif
            //该word_id对应倒排遍历下一个文档
            bool is_end = (*collector_iter).next();
            if(is_end){

                #ifdef DEBUG
                    cout<<"erase word_id iter:"<<collector_iter->get_word_id()<<endl;
                    cout<<"collector size:"<<_collector_vec.size()<<endl;

                #endif
                //如果该word_id对应倒排已经遍历完毕，则删除
                collector_iter = _collector_vec.erase(collector_iter);
            }else{
                //遍历下一个word_id指向的倒排
                ++collector_iter;
            }
        }

            #ifdef DEBUG
                cout<<endl;
                cout<<first_doc_id<<" end_score:"<<score<<endl; 
            #endif

        //将文档打分与目前选中文档打分比较，判断是否选入
        DocScore doc_score;
        doc_score.doc_id = first_doc_id;
        doc_score.doc_score = score;
        if(_score_vec.size() < RESULT_SIZE){
            _score_vec.push_back(doc_score);
            if(_score_vec.size() == RESULT_SIZE){
                make_heap(_score_vec.begin(),_score_vec.end(),Rank::score_sort);
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

                //_score_vec[0] = doc_score;
                _score_vec.push_back(doc_score); 
                std::push_heap(_score_vec.begin(),_score_vec.end(),Rank::score_sort);
            }
        }
   }
}

double SimRank::get_score(Collector & collector){
    //bm25计算当前文档分值
    double idf = collector.get_query_idf();
    int tf = collector.get_query_doc_tf();
    double average_len = collector.get_average_length();
    double doc_len = collector.get_doc_length();
    double score = idf * ( tf * (1.5 + 1) ) / ( tf + 1.5 * ( 1 - 0.75 + 0.75 * doc_len/average_len));
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
