#!/usr/bin/env python
# -*- coding:utf8 -*-
from __future__ import print_function
import sys

preterm=""
predoclist=[]
predocid=-1
pretf=-1
term=""

for line in sys.stdin:
    line = line.strip()
    lines = line.split('\t')
    if len(lines) != 3:
        continue
    term=lines[0]
    docid = lines[1]
    tf = lines[2]
    if term == preterm:
        print("|%s#%s" %(docid, tf), end='')
    else:
        if preterm != "":
            print("")
        preterm=term
        print("%s|%s#%s" %(term, docid, tf), end=''), 
        sys.stdout.flush()

if term == preterm and term != "":
    print("|%s#%s\n" %(docid, tf), end=''), 
else:
    if preterm != "":
        print("")
    preterm=term
    print("%s|%s#%s\n" %(term, docid, tf), end=''), 

