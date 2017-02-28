#! /usr/bin/env python
# coding=utf-8

import sys
import math

class rank_item:
    def __init__(self, title, url, label):
        self.title = title
        self.url = url
        self.label = int(label)

def top3_dcg(rank_list):
    total_dcg = 0
    item_count = 0
    for item in rank_list:
        dcg = (pow(2, item.label) - 1) / (math.log10(2 + item_count) / math.log10(2))
        total_dcg += dcg
        item_count += 1
        if item_count >= 3:
            break
    return total_dcg

def calc_ndcg(rank_ideal, rank_real, key_list):
    ndcg_list = []
    for key in key_list:
        if key not in rank_real or key not in rank_ideal:
            continue
        ideal_dcg = top3_dcg(rank_ideal[key])
        real_dcg = top3_dcg(rank_real[key])
        ndcg_list.append((key, (real_dcg + 0.000001) / (ideal_dcg + 0.000001)))
    return ndcg_list

def read_data(file):
    data = {}
    for line in file:
        line = line.strip()
        if line == '':
            continue
        fields = line.split('\t')
        if len(fields) != 4:
            continue
        (query, title, url, label) = fields
        if query not in data:
            data[query] = []
        data[query].append(rank_item(title, url, label))
    return data

def evaluate():
    if len(sys.argv) != 3:
        print "USAGE:", sys.argv[0], "label_file", "rank_file"
        exit(-1)

    # init rank_ideal
    label_file = open(sys.argv[1], 'r')
    label_data = read_data(label_file)
    label_file.close()
    for query in label_data:
        label_data[query].sort(lambda x,y:cmp(y.label, x.label))

    # init rank_real
    rank_file = open(sys.argv[2], 'r')
    rank_real = read_data(rank_file)
    rank_file.close()

    # compute ndcg
    ndcg_list = calc_ndcg(label_data, rank_real, rank_real.keys())
    avg_ndcg = sum([ndcg for key,ndcg in ndcg_list]) / len(ndcg_list)

    # result
    print 'avg_ndcg@3 :', avg_ndcg
    print 'item_count :', len(ndcg_list)

    debug_out = open('debug.result', 'w')
    ndcg_list.sort(lambda x,y:cmp(x[1], y[1]))
    for query,ndcg in ndcg_list:
        if query not in rank_real or query not in label_data:
            continue
        debug_out.write('%s\n'%query)
        debug_out.write('ndcg@3 : %.3f\n'%ndcg)
        debug_out.write('[real_rank]\n')
        for item in rank_real[query]:
            debug_out.write('%d\t%s\t%s\n'%(item.label, item.title, item.url))
        debug_out.write('[ideal_rank]\n')
        for item in label_data[query]:
            debug_out.write('%d\t%s\t%s\n'%(item.label, item.title, item.url))
        debug_out.write('\n')
    debug_out.close()

if __name__ == "__main__":
    evaluate()
