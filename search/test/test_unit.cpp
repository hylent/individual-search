/***************************************************************************
 * 
 * Copyright (c) 2016, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file test_unit.cpp
 * @author caolin
 * @date 2016/06/11 18:43:13
 * @brief 
 *  
 **/

#include "indexer.h"
#include "word_dict.h"
#include "segment.h"
#include "searcher.h"
#include <unistd.h>
namespace cute_engine{
using std::cout;
using std::endl;

class TestUnit{
    public:

        
        void static test_build_index(char* raw_index_file, char *raw_data_file,char* dict_path,char* output_path){

            cout << "raw_index_file:" << raw_index_file << endl;
            cout << "raw_data_file:" << raw_data_file << endl;
            cout << "dict_path:" << dict_path << endl;
            cout << "output_index_path:" << output_path << endl;
            Indexer indexer(output_path);
            //顺序很重要，先计算brief信息
            //indexer.build_document_info(raw_data_file, output_path);
            //indexer.build_inverted_index_from_file(raw_index_file, dict_path, output_path);
            //indexer.build_term_upper_bound();
        }
        
        void static test_search(char *raw_data_path,char* dict_path,char* search_path){
            /*
            Segment *psegment = new Segment();
            psegment->init(dict_path,1024);
            WordDict *pword_dict = new WordDict();
            Indexer indexer(psegment,pword_dict);

            indexer.build_forward_index(raw_data_path, dict_path);
            indexer.build_inverted_index_from_forward_index();

            indexer.output_document_index("./docindex.txt");
            indexer.output_dict("./dict.txt");
            indexer.output_inverted_index("./");

            int average_len = indexer.get_average_length();
            int total_doc_num = indexer.get_total_doc_num();
            cout<<"ava_len:"<<average_len<<endl;
            cout<<"total_doc_num:"<<total_doc_num<<endl;

            std::map<size_t,WordItem>& inverted_index = indexer.get_inverted_index();
            vector<Hit> & hit_list = indexer.get_hit_list();
            vector<InvertedPosting> & inverted_post_list = indexer.get_inverted_posting_list();
            std::map<int,DocumentInfo>& docs_info = indexer.get_docs_info();
            Searcher search(psegment,pword_dict);
            search.set_average_length(average_len);
            search.set_total_doc_num(total_doc_num);

            search.set_inverted_index(inverted_index);
            search.set_inverted_posting_list(inverted_post_list);
            search.set_hit_list(hit_list);
            search.set_docs_info(docs_info);

            search.test_search(search_path);
            delete psegment;
            delete pword_dict;
            */
        }

        void static test_load_data(char *path){
            Indexer index;
            index.load_index_meta_data(path);
            index.load_inverted_index();
        }
       
        void static test_index_search(char* index_path, char *dict_path,
                                      char* forward_db_path, char * query_file){
            //Indexer index;
            //index.load_index_data(data_path);
            //index.load_inverted_index();
            Searcher search(index_path, dict_path, forward_db_path);
            search.test_search(query_file);
        }
        //词典测试
        void static test_worddict(char* inpath, char* outpath) {
            WordDict* dict = new WordDict();
            dict->load_dict(inpath);
            string word("龟背");
            DictInfo* info = dict->get_word_info(word);
            printf("%s\t%u\t%u\t%u\t%ld\t%ld\n", const_cast<char*>(word.c_str()), info->df, info->dict_id, info->file_index, info->offset_begin, info->offset_end);
            info->file_index = 1;
            dict->output_dict(outpath);
        }
            
    
        void static test_word_segment(char *raw_data_path,char * dict_path) {
            Segment wordseg;
            wordseg.test(raw_data_path,dict_path);
        }

        void static usage() {
            cout << "usage: test_unit -b build_raw_file -f raw_txt_file -d dict_path -i index_path " << endl;
            cout << "       test_unit -s search_raw_file -d dict_path -i index_path -w forward_path" << endl;
        }
};

}

using cute_engine::TestUnit;

int main(int argc,char ** argv){
    int opt;
    char* data_file = NULL;
    char* dict_path = NULL;
    char* index_path = NULL;
    char* forward_path = NULL;
    char* txt_file = NULL;
    bool is_build = false;
    bool is_search = false;
    while((opt = getopt(argc, argv, "hb:s:d:i:f:w:")) != -1) {
        switch (opt) {
            case 'h':
                TestUnit::usage();
                break;
            case 'b':
                data_file = optarg;
                is_build = true;
                break;
            case 's':
                data_file = optarg;
                is_search = true;
                break;
            case 'd':
                dict_path = optarg;
                break;
            case 'i':
                index_path = optarg;
                break;
            case 'f':
                txt_file = optarg;
                break;
            case 'w':
                forward_path = optarg;
                break;
        }
    }
    //TestUnit::test_worddict(argv[1], argv[2]);
    if (is_build) {
        TestUnit::test_build_index(data_file, txt_file, dict_path, index_path); 
    } else if (is_search) {
        //index_path dict_path query_path
        TestUnit::test_index_search(index_path, dict_path, forward_path, data_file); 
    }
    //TestUnit::test_search(argv[1],argv[2],argv[3]); 
    //TestUnit::test_load_data(argv[1]);
    //TestUnit::test_word_segment(argv[1],argv[2]); 
}


/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
