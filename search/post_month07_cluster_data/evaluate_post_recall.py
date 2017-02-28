#!/usr/bin/env python
# -*- coding:utf8 -*-
import sys

def main():
    line_count = 0;
    pre_id = 0
    pre_line = ""
    for line in open(sys.argv[1], 'r'):
        line_count += 1
        if line_count %3 == 1:
            lines = line.strip().split("\t")
            pre_id = lines[0]
            pre_line = line
        elif line_count%3 == 0:
            lines = line.strip().split()
            item_cnt = len(lines)
            hit = False
            for i in range(1, item_cnt):
                items = lines[i].split(":")
                if items[0] == pre_id:
                    sys.stdout.write('%s %d\n' %(pre_id, i))
                    hit =True
            if hit is False:
                sys.stdout.write('nothit\n')
                #pass
                #sys.stdout.write('%s' %pre_line)
        #if line_count > 6:
        #    sys.exit()
def lowfile():
    for line in open(sys.argv[1], 'r'):
        print line.strip().lower()
if __name__ == '__main__':
    main()
    #lowfile()
