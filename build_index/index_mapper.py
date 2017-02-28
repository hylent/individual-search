#!/usr/bin/env python
# -*- coding:utf8 -*-

import sys
sys.path.append('./')
import jieba

def strQ2B(string):
    """全角转半角"""
    rstring = ""
    ustring = string.decode('utf8')
    for uchar in ustring:
        inside_code=ord(uchar)
        if inside_code == 12288:                              #全角空格直接转换            
            inside_code = 32
        elif (inside_code >= 65281 and inside_code <= 65374): #全角字符（除空格）根据关系转化
            inside_code -= 65248

        rstring += unichr(inside_code)
    return rstring.encode('utf8')

def strB2Q(string):
    """半角转全角"""
    ustring = string.decode('utf8')
    rstring = ""
    for uchar in ustring:
        inside_code=ord(uchar)
        if inside_code == 32:                                 #半角空格直接转化                  
            inside_code = 12288
        elif inside_code >= 32 and inside_code <= 126:        #半角字符（除空格）根据关系转化
            inside_code += 65248

        rstring += unichr(inside_code)
    return rstring.encode('utf8')

def preprocess(line):
    line = strQ2B(line)
    return line.lower()

def loadstopword():
    stopwords = []
    for line in open('stopword.txt', 'r'): 
        stopwords.append(line.strip())
    return stopwords 
        
def main():
    stopwords = loadstopword()
    for line in sys.stdin:
        line = line.strip()
        lines = line.split('\t')
        if len(lines) != 4:
            continue
        docid = lines[0]
        content = lines[3]
        terms_tf = {}
        content_list = jieba.lcut_for_search(content)
        #content_list = jieba.lcut(content, cut_all=True)
        for word in content_list:
            low_word = word.lower()
            terms_tf[low_word] = terms_tf.setdefault(low_word, 0) + 1 
        for term, tf in terms_tf.items():
            term_utf = term.encode('utf8')
            if term_utf in stopwords or term_utf == " ":
                continue
                #print "%s is stopwords" %term_utf
            print "%s\t%s\t%d" %(term.encode('utf8'), docid, tf) 
            
if __name__ == '__main__':
    main()
