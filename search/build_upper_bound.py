#!/usr/bin/env python
# -*- coding:utf8 -*-
import sys
import math

def build_upper_bound(raw_file, index_path):

    #load meta data
    meta_path = index_path + "/metainfo.dat"
    ave_length = 0
    total_doc_count = 0
    for line in open(meta_path, 'r'):
        lines = line.strip().split("\t")
        if len(lines) < 2:
            print "meta info error"
            sys.exit()
        ave_length =  int(lines[0])
        total_doc_count = int(lines[1])

    #load dict data
    dict_path = index_path + "/worddict.dat"
    word_dict = {}
    for line in open(dict_path, 'r'):
        lines = line.strip().split("\t")
        if len(lines) < 6:
            print " format error: %s" %(line) 
        #print line
        word_df = int(lines[1])
        #math.log 以e为底
        word_idf = math.log(float(total_doc_count + 0.5) / (word_df + 0.5))
        word_dict[lines[0]] = word_idf

    #load doc_len data
    doc_info_path = index_path + "/docinfo.dat"
    docs_info = {}
    for line in open(doc_info_path, 'r'):
        lines = line.strip().split("\t")
        if len(lines) < 2:
            print "doc info error"
        doc_id = lines[0]
        doc_len = int(lines[1])
        docs_info[doc_id] = doc_len

    #load index_data
    dict_bound = {}

    for line in open(raw_file, 'r'):
        lines = line.strip().split("\t")
        if len(lines) < 2:
            print "raw_data format error"
        word = lines[0]
        if word not in  word_dict:
            continue
        word_idf = word_dict[word]
        bound = 0.0
        docs = lines[1].split("|")
        for doc in docs:
            doc_info = doc.split("#")
            doc_id = doc_info[0]
            doc_tf = int(doc_info[1])
            doc_len = float(docs_info[doc_id])
            value = doc_tf * (1.5+1)/ (doc_tf+1.5*(0.25+0.75*doc_len/ave_length))
            #print word, doc_tf, doc_id, doc_len, ave_length, value 
            if value > bound:
                bound = value
        dict_bound[word] = bound * word_dict[word]
        #print word, bound, word_dict[word], dict_bound[word]

    dict_path = index_path + "/worddict.dat"
    #with open(new_dict_path, 'w') as fh:
    for line in open(dict_path, 'r'):
        line = line.strip()
        lines = line.split("\t")
        if len(lines) < 6:
            print " format error: %s" %(line) 
        word = lines[0]
        word_bound = dict_bound.get(word, 0.0)
        print "%s\t%lf" %(line, word_bound)

def usage():
    print "Usage:python build_upper_bound.py raw_index_file index_path"
if __name__ == '__main__':
    if len(sys.argv) < 3:
        usage()
        sys.exit()
    build_upper_bound(sys.argv[1], sys.argv[2])
