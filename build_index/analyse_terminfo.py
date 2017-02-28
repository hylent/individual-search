#!/usr/bin/env python
# -*- encoding:utf8 -*-
import sys

def main():
    for line in open(sys.argv[1], 'r'):
        lines = line.strip().split('\t')
        if len(lines) != 2:
            continue
        docs = lines[1].split('|')
        df = len(docs)
        print "%s\t%d" %(lines[0], df)

if __name__ == '__main__':
    main()
