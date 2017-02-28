#!/usr/bin/env python
# -*- coding:utf8 -*-

import sys
import re

def main():
    preline = ""
    preid = 0
    for line in open(sys.argv[1], 'r'):
        lines = line.strip().split("\t")
        if len(lines) == 2 and re.search('^\d+', lines[0]):
            preline = line.strip()
            preid = lines[0]
            #print preid, preline
            continue
        if re.search('^final_result:', line):
            lines = line.strip().split(" ")
            idx = 0
            found = False
            #print line.strip()
            for item in lines:
                items = item.split("|")
                if len(items) != 2:
                    continue
                idx += 1
                tmpid = items[0].split(":")[0]
                tmpprob = items[0].split(":")[1]
                if tmpid == preid:
                    print tmpid, idx, tmpprob, preline
                    found = True
                    break
            if found is False:
               print preid, -1, 0.0, preline



if __name__ == '__main__':
    main()
