/***************************************************************************
 * 
 * Copyright (c) 2011 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file test_odict.cpp
 * @author lichenggang(com@baidu.com)
 * @date 2011/02/22 18:41:30
 * @brief 
 *  
 **/

#include <iostream>
#include "ul_dict.h"
#include "ul_sign.h"

using std::cerr;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    char name[1024];
    char value[1024];

    if (2 != argc)
    {
        fprintf(stderr, "USAGE: %s raw_data\n", argv[0]);
        return -1;
    }

    FILE *fin = fopen(argv[1], "r");
    if (NULL == fin) 
    {
        fprintf(stderr, "open file failed, filename=%s\n", argv[1]);
        return -1;
    }

    Sdict_build *dict = db_creat(1024, 0);
    
    while (fscanf(fin, "%s%s", name, value) != EOF) 
    {
        Sdict_snode snode;
        creat_sign_f64(name, strlen(name), &snode.sign1, &snode.sign2);
        snode.other = atoi(value);
        int ret = db_op1(dict, &snode, ADD);
        if (-1 == ret) 
        {
            fprintf(stderr, "add to dict error, name=%s value=%s\n", name, value);
            return -1;
        }

        db_op1(dict, &snode, MOD);
        fprintf(stdout, "%s added\n", name);
    }

    fseek(fin, 0, SEEK_SET); 

    while (fscanf(fin, "%s%s", name, value) != EOF) 
    {
        Sdict_snode snode;
        creat_sign_f64(name, strlen(name), &snode.sign1, &snode.sign2);
        if (db_op1(dict, &snode, SEEK) == 1) 
        {
            fprintf(stdout, "%s:%d\n", name, snode.other);
        }
        else 
        {
            fprintf(stderr, "%s not found\n", name);
        }
    }

    fclose(fin);
    db_del(dict);

    return 0;
}





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
