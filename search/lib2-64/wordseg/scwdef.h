/*
 * filename    : scwdef.h
 * author      : Paul Yang
 * version     : 
 * date        : 2004.12.1
 * description : interface and definition file of segment module.
 */

#ifndef SCWDEF_H
#define SCWDEF_H

#include <stdio.h>
#include <ul_dict.h>
#include <ul_sign.h>
#include <ul_log.h>
#include <assert.h>
#include <stdint.h>
#include "property.h"
#include "lib_crf.h"
#include "ul_dictmatch.h"
#include "odict.h"
#include "ul_ccode.h"


// micros defined here
//--------------------------------------------------------------------------------//
#define MAX_WORD_LEN 256
#define DEFAULT_AMB_NUM 256
#define SCW_MAX_VERSION_LEN 100
#define SCW_MAX_INNER_TERM 256
#define MAX_EXTEND_PHINFO_SIZE 770
#define MAX_POT_LEMMA_SIZE 100//每个切分片段有可能增加的lemma个数，如果超过，则不添加该term
#define MAX_EXTEND_ENTRY_SIZE 100000
#define LEMMA_ADD_SIZE 10000//每次lemmalist增加个数
#define MAX_NBEST 1 //crf nbest
#define MAX_CRFTAG_NBEST 5 //crf nbest

#define SCW_OUT_PROP 1
#define SCW_OUT_BASIC  2
#define SCW_OUT_WPCOMP 4
#define SCW_OUT_SUBPH   8
#define SCW_OUT_HUMANNAME 16
#define SCW_OUT_BOOKNAME 32
#define SCW_OUT_NEWWORD 64
#define SCW_OUT_DISAMB    128
#define SCW_OUT_ALL 255

#define SCW_CRF    1
#define SCW_TN    2
#define SCW_HUMAN_ALLOW_BLANK    4
#define SCW_LGT    8
#define SCW_USE_BLANK    16    //default的空格切分开关
#define SCW_TCC_MERGE    32    //thai的tcc merge后处理开关
#define SCW_ASC_MERGE    64    //english, arabic, thai, vietnam的asc动态合并后处理
#define SCW_DISAMB    128    //中文多切分标志
#define SCW_CONF_ALL    255

#define SCW_STATIC 0
#define SCW_DYNAMIC 1
#define SCW_DICTNAME "worddict.scw"
#define SCW_NEWWORDDICT "newword"
#define SCW_LSN_RULEFILE "leftrule"
#define SCW_RSN_RULEFILE "rightrule"
#define SCW_VERINFONAME "version.scw"
#define SCW_DICTVER_TAG "DictVer"
#define SCW_VERMAP_TAG "VerMap"
#define SCW_MANNAME "worddict.man"  //人工控制文件名称
#define CRF_MODEL_NAME "crf_model"
#define SCW_MULTIDICT "multi_dict"
#define SCW_CONFIGURE "scw.conf"
#define SCW_TRANSDICT "transdict"  //繁简转换词典名称
//中文特有结构
#define SCW_PHRASE_SUB    "phrasesub"
#define SCW_NER_DICT    "nedict"

#define MAX_VERSION_NUM 1024

#define WORDSEG_MAX_CONF_ITEM_SIZE 256 /**<每个item的最大尺寸 */
#define WORDSEG_MAX_CONF_SECTION_NUM 32 /**< 配置支持的最大section数量 */
#define WORDSEG_MAX_CONF_ITEM_NUM 16 /**< 每个section支持的最大item数量 */

#define DATA_INAME 0
#define DATA_FNAME 1
//#define DATA_JNAME 2
//
#define MIN_SPECSTR_LEN 3
#define MIN_LTR_LEN 1

//繁简转换字典所用
#define SCW_GBK_1NUM 0x7e    //126
#define SCW_GBK_2NUM 0xbf    //191
#define SCW_GBK_NUM 0x5e02   //24066

#define GET_TERM_POS(property)  ((property) & 0x00FFFFFF)
#define GET_TERM_LEN(property)  (((unsigned)property) >> 24)

typedef struct _SCW_VERSION_MAP
{  
  Sdict_build * m_sver_dict;
  Sdict_build * m_dver_dict;
  
  char * m_strbuf;
  unsigned int m_bufsize;
  unsigned int m_bufpos;

  unsigned int m_sver_count;
  unsigned int m_dver_count;
  
  char m_ver_table[MAX_VERSION_NUM][MAX_VERSION_NUM];
}scw_ver_map;

  
// constant defined here
//--------------------------------------------------------------------------------//
const unsigned int DEFAULT_LEMMA_COUNT = 1000;
const unsigned int DEFAULT_INFO_SIZE = 4000;
const unsigned int DEFAULT_DE_SIZE = 2000;
const unsigned int DEFAULT_WORDBUF_SIZE = 20000;
const unsigned int DEFAULT_HASH_SIZE = 1;
const unsigned int DENTRY_NULL = 0xFFFFFFFF;
const unsigned int DENTRY_FIRST = 0xFFFFFFFE;
const unsigned int SUFENTRY_NULL = 0xFFFFFFFF;
const unsigned int LEMMA_NULL = 0xFFFFFFFF;
const unsigned int COMMON_NULL = 0xFFFFFFFF;

const unsigned int LEMMA_TYPE_SBASIC = 0;
const unsigned int LEMMA_TYPE_DBASIC = 1;
const unsigned int LEMMA_TYPE_SPHRASE = 2;
const unsigned int LEMMA_TYPE_DPHRASE = 3;
const unsigned int LEMMA_TYPE_QYPD = 4;
const unsigned int LEMMA_TYPE_POLY = 5;
const unsigned int LEMMA_TYPE_MAN = 6;//人工控制片段

const unsigned int MAX_LEMMA_LENGTH = 256;
const unsigned int MAX_AMB_NUM = 256;
const unsigned int MAX_IL_LEN = 2408;
const unsigned int MAX_LEMMA_POS = 0x80000000;
const unsigned int SCW_INFO_FACT = 8;

const int AUX_WEIGHT_INC = 1000;
const int WORDELE_WEIGHT_INC = -200;

const unsigned int SCW_MAXWORDLEN = 256;

const double LEMMA_SMOOTH_PROB = 1e-11;
const double LEMMA_DEFAULT_PROB = 0.0333;
const int NORMALIZE_INTEGER = 10000;

const double LEMMA_SMOOTH_PROB_JP = 2e-11;
const double LEMMA_DEFAULT_PROB_JP = 1e-11;

const unsigned int NAME_PROP_COUNT = 4;
const unsigned int MAX_SPLIT_NUM = 256;
const int MAX_TERM = 10000000;
//const unsigned int CRF_BUF_SIZE = 512;
const unsigned int TYPE_NEWWORD = 0;
const unsigned int TYPE_MULTITERM = 1;
const unsigned int TYPE_MULTITERM_NEWWORD = 2;
enum NAME_POS{NAME_BGN,NAME_MID,NAME_END,NAME_OTH};


/*-------------------crf for wordseg preprpocessing -----------------*/

typedef struct scw_crf_term_t
{
    unsigned int wordtotallen;          // 当前被切分文本长度（不含用于分隔切分片段的'\t'）    
    unsigned int crftermcount;          // 切分片段数目
  //  unsigned int* crftermoffsets;        // 基本词计数，也就是当前切分片段是从第几个基本词开始的
    unsigned int* crftermpos;           // 当前切分片段的字节偏移以及长度，整数的低24bit为偏移，高8bit为长度
}scw_crf_term;

typedef struct scw_crf_out_t
{
    int nbest;                   // 返回的nbest值
    scw_crf_term term_buf[MAX_NBEST];
}scw_crf_out;

//phrase子成分字典结构
typedef struct PHRASE_DICT_T
{
    Sdict_search* m_subindex; //使用uldict保存phrase词条
    int *m_subpos; //保存偏移信息
    int m_subpos_cnt; //偏移数组的大小
    char* m_subbuf; //保存子term字符串形式
    int m_subbuf_len; //subbuf的长度
}phrase_sub_dict;
//新词切分字典
/*typedef struct NEWWORD_DIS_DICT_T
{
    Sdict_search* m_newword;
    int *m_newwordseg_pos;
    int m_newwordseg_cnt;
}newword_dis_dict_t;*/
//中文特有字典
typedef struct _CHS_LANG_DICT_T
{
    phrase_sub_dict* phrasesubdict;
    sodict_search_t* nerworddict;
    unsigned char* transdict;
    //newword_dis_dict_t* newword_disdict;
}chs_lang_dict_t;

// data structure defined here
//--------------------------------------------------------------------------------//
/* 词语属性记录 */
typedef struct SCW_PROPERTY_T
{
  int m_hprop;
  int m_lprop;
}scw_property_t;

/* 词条结构 */
typedef struct SCW_LEMMA_T
{
  unsigned m_type:3;
  unsigned m_weight:21;        // the lemma's weight
  unsigned m_length:8;

  scw_property_t m_property;   // some property of the lemma

  union
  {
    unsigned int m_word_bpos;         // 基本词词条开始位置
    unsigned int m_phinfo_bpos;       // 短语词条开始位置，指向一个整型数组的开始位置，该数组第一个元素存储此词条所含基本词的个数，后面依次为每一个基本词的词条指针
  };
  
  unsigned int m_subphinfo_bpos;      // 子短语词条开始位置，指向一个整型数组的开始位置，数组的第一位存储此词条子短语的个数，假设为M个，则接下来的2*M的空间中，依次存储第i个子短语的内部偏移量(以基本词个数来计算)，以及第i个字短语的lemma指针
  unsigned int m_prelm_pos;           // the position of the prelemma
  unsigned int m_utilinfo_pos;
}scw_lemma_t;

typedef struct SCW_UTILITYINFO_T
{
  unsigned int m_ambsuffix_pos;
  unsigned int m_inameprob_pos;
  unsigned int m_fnameprob_pos; 
}scw_utilinfo_t;

/* 仅在生成词典时使用 */
typedef struct SCW_INPUTLEMMA_T
{
  char m_lmstr[SCW_MAXWORDLEN];
  unsigned int m_type; // 词条类型，如静态基本词等
  unsigned int m_weight;
  scw_property_t m_property;

  int m_bwcount;
  int m_sphcount;
  unsigned int  m_wordlist[512];  // 两个整数一组，前一个整数表示基本词在当前字符串中序号，后一个表示其存储位置
  unsigned int  m_subphlist[512]; // 两个整数一组，前一个整数表示短语在当前字符串中序号，后一个表示其存储位置
  
  unsigned int   m_mcount;//人工控制部分切分个数
  unsigned int  m_manuallist[512];//人工控制片段结果，如果是静态词，存储该lemma在lemmalist中的偏移量，如果是动态词，存储该lemma在pwdict->pir->m_dynlm中的偏移量。
}scw_inlemma_t;

/* 新词buffer结构*/
typedef struct SCW_NEWWORD_T
{
    char*  newwordbuf;
    unsigned int  newwordbsize;
    unsigned int  newwordb_curpos;
    unsigned int  newwordbtermcount;
    unsigned int  newwordbmaxcount;
    unsigned int* newwordbtermoffsets;//同ne buffer，每个term的offset要存两位，一位存起始的混排的term位置，另一位存储包含的混排的term个数，在初始化的时候offset buffer的size要乘2
    unsigned int* newwordbtermpos;
    neprop_t* newwordneprop;           // wordner的相关信?
    scw_property_t* newwordbtermprop;
}scw_newword_t;

/* trie树中每个节点的结构*/
typedef struct SCW_DICTENTRY_T
{
  unsigned int m_value;      // 结点汉字或者别的字符对应的整型值
  unsigned int m_lemma_pos;  // 指向当前entry所对应的lemma位置，这个lemma是指Trie树从根节点到此节点路径上能匹配的词语。
  unsigned int m_suffix_pos; // 指向后续结点的开始位置
}scw_dictentry_t;

/**
 * 国际化结构体
 */
//语言相关的词典结构
typedef struct _SCW_WORDDICT_T
{
  /// store the strings of terms.
  char* m_wordbuf;              // buffer for store word  result;
  unsigned int m_wbsize;
  unsigned int m_wbpos;                // the next position in word buf

  /// store the phrase info.
  unsigned int* m_phinfo;              // the buffer for phrase information and sub phrase information
  unsigned int m_phisize;
  unsigned int m_phipos;               // the unused pos in ph info list

  //store the dynamic phrase and basic info
  char*          m_dynbuf;         //the buffer for dynamic basic infomation
  unsigned int          m_dynb_size;
  unsigned int          m_dynb_curpos;

  unsigned int*         m_dynphinfo;  //the buffer for dynamic phrase infomation
  unsigned int          m_dynph_size;
  unsigned int          m_dynph_curpos;

  /// store the node nexus.
  unsigned int* m_seinfo;              // the node nexus list
  unsigned int m_seisize;
  unsigned int m_seipos;

  /// store the node contents.
  scw_dictentry_t* m_dictentry; // the dict entry list
  unsigned int m_desize;
  unsigned int m_depos;                // the first unused pos in node list

  /// store the lemma structure of dictionary.
  scw_lemma_t* m_lemmalist;     // the lemma list
  unsigned int m_lmsize;
  unsigned int m_lmpos;                // the first unused pos in lemma list, ending position

  /// root node of trie tree.
  unsigned int m_entrance;

  Sdict_search* pdict_lsn_rule;
  Sdict_search* pdict_rsn_rule;

  int* m_probbuf;
  unsigned int m_pbsize;
  unsigned int m_pbpos;

  unsigned int* m_ambinfo;
  unsigned int m_ambsize;
  unsigned int m_ambpos;

  scw_utilinfo_t* m_utilinfo;
  unsigned int m_utilisize;
  unsigned int m_utilipos;

  unsigned int m_wdtype;

  char version[SCW_MAX_VERSION_LEN];

  void * preserved; //预留其他语言相关资源指针

  // 以下这几个是新切词模型引入的CRF和新词控制词典，减少修改代价
  // 也可以放入预留指针
  CrfModel *crf_model;
  sodict_search_t* newworddict;//新词控制词典
  dm_dict_t* multitermdict;//新词控制词典
}scw_lang_dict_t;

//全局字典结构体
typedef struct _SCW_GLOBAL_DICT_T
{
    scw_lang_dict_t ** ppdict; //各个语言的词典资源
    volatile int* dict_dyn_flag;
    int dict_num;//可用的词典数
}scw_worddict_t;

/* inner接口，定义不变 */
typedef struct _SCW_INNER_T
{
  unsigned int    m_maxterm;       // 分词结果所能容纳最大基本词数
  unsigned int    m_flag;          // 分词结果数据控制开关
  unsigned int    m_merged_flag;   // 为粘接服务
  unsigned int    m_offset;        // 分词结果基本词偏移量

  /// store segmented lemmas.
  scw_lemma_t**  m_ppseg;   // 记录切分结果(混排)中词条地址序列，如果词条是动态生成的，则指向<m_dynlm>中元素的地址
  unsigned int  m_ppseg_cnt;
  int* m_ppseg_flag;

  scw_lemma_t** tmp_ppseg;// 记录最原始querywordseg的切分结果；需要从m_ppseg中copy过来
  unsigned int tmp_ppseg_cnt;


  /// store dynamic terms.
  char*  m_dynbuf;
  unsigned int  m_dynb_size;
  unsigned int  m_dynb_curpos;

  uintptr_t* m_dynphinfo;   // 记录动态短语信息
  unsigned int      m_dynph_size;
  unsigned int      m_dynph_curpos;

  uintptr_t* m_dynphinfo_tmp;   // 新增一个动态短语信息，用于ascii码识别考虑。
  unsigned int      m_dynph_size_tmp;
  unsigned int      m_dynph_curpos_tmp;


  scw_lemma_t*  m_dynlm;    // 用来记录切分过程中生成的动态词条
  unsigned int    m_dynlm_size;
  unsigned int    m_dynlm_cnt;
  
  unsigned int *m_mandictword_prop;    //记录query中包含worddict.man中词条的信息，每个单元的高八位是长度信息，低24位是偏移信息
  unsigned int m_mandictword_size;
  unsigned int m_mandictword_cnt;

  unsigned int* pos_property;    //ascii串再切分需要的结构,用于保存临时切分结果
  unsigned int pos_property_size;

  scw_newword_t* pnewword; //新词接口
  scw_newword_t* pdisambword;    //歧义切分结果

  //ner_out_t *pnerout;  //wordner识别结果，不一定有必要，这个要考虑

  crf_out_t* crf_out;    //crf的切词结果的输出
  scw_crf_out* crf_res;
  SegCrfTag *crf_tag; //crf_tag

  char* m_tmpbuf;//用来装载加保护后的半切分结果，送与wordseg切分。
  unsigned int m_tmpbuf_len;
  unsigned int* m_protect; //用来记录保护crf词典词的标签的位置。
  unsigned int m_protect_cnt;
  bool needremove; //用来标注是否需要removetag

  dm_pack_t* multiterm_pack;


  unsigned int* basic_offset; //对于繁体切分，需要在write_buf的时候，将其简体结果转成繁体形式，这个变量保留了basic结果的offset
  unsigned int basic_cnt; //对应basic_offset的使用大小

}scw_inner_t;

/* 语言相关的扩展内容 */
typedef struct _SCW_LANG_INNER_T
{
  void * preserved; //语言扩展内容，由各语言自行申请指定，如：词性、读音、stemming结果等
}scw_lang_inner_t;

//scw_out_t
typedef struct _SCW_OUT_T
{
//public:用户可见 0-5
  //0 basic word sep result
  char* wordsepbuf;            // 字符缓冲（需预先初始化），用于存储分词结果
  unsigned int wsbsize;               // 字符缓冲大小（初始化缓冲区时给定）
  unsigned int wsb_curpos;            // 当前可用缓冲区开始为位置
  unsigned int wordtotallen;          // 当前被切分文本长度（不含用于分隔切分片段的'\t'）
  unsigned int wsbtermcount;          // 切分片段数目
  unsigned int* wsbtermoffsets;       // 基本词计数，也就是当前切分片段是从第几个基本词开始的
  unsigned int* wsbtermpos;           // 当前切分片段的字节偏移以及长度，整数的低24bit为偏移，高8bit为长度
  scw_property_t* wsbtermprop; // 各切分片段的属性信息

  //1 word phrase sep result
  char* wpcompbuf;
  unsigned int wpbsize;
  unsigned int wpb_curpos;
  unsigned int wpbtermcount;
  unsigned int* wpbtermoffsets;
  unsigned int* wpbtermpos;
  scw_property_t* wpbtermprop;

  //2 sub-phrase result
  char*  subphrbuf;
  unsigned int  spbsize;
  unsigned int  spb_curpos;
  unsigned int  spbtermcount;
  unsigned int*  spbtermoffsets;
  unsigned int*  spbtermpos;
  scw_property_t * spbtermprop;

  //3 human name result
  char*  namebuf;
  unsigned int  namebsize;
  unsigned int  nameb_curpos;
  unsigned int  namebtermcount;
  unsigned int* namebtermoffsets;
  unsigned int* namebtermpos;
  scw_property_t * namebtermprop;

  //4 book name result
  char*  booknamebuf;
  unsigned int   bnbsize;
  unsigned int   bnb_curpos;
  unsigned int   bnbtermcount;
  unsigned int*  bnbtermoffsets;
  unsigned int*  bnbtermpos;
  scw_property_t * bnbtermprop;

  //5 internal buffer for term merging
  int  phrase_merged;
  char*  mergebuf;
  unsigned int   mbsize;
  unsigned int   mb_curpos;
  unsigned int   mbtermcount;
  unsigned int*  mbtermoffsets;
  unsigned int*  mbtermpos;
  //新词和大粒度词buffer，用户可见
  scw_newword_t* pnewword;
  scw_newword_t* pdisambword;

//private:不建议使用方使用，这是一个中间结果保存单元
  scw_inner_t * m_pir; 
  /* 以下内容封装为一个语言相关输出结构，由各个语言自行填写 */
  scw_lang_inner_t ** pplir;  //各语言扩展内容指针
}scw_out_t;

/**
 * @brief short description
 * 配置item的key-value数据对
 */
typedef struct _SCW_KVPAIR_T
{
    char achKey[WORDSEG_MAX_CONF_ITEM_SIZE]; /**< 每一个key-value对中的key*/
    char achValue[WORDSEG_MAX_CONF_ITEM_SIZE]; /**< 每一个key-value对中的value*/
}scw_kvpair_t;

/*
 * @brief short description
 * 配置section项数据结构
 */
typedef struct _SCW_CONF_SECTION_T
{
    int section_id; /**< section id */
    int pair_num; /**< section内的item数量 */
    scw_kvpair_t *kv_conf; /**< item数组 */
}scw_conf_section_t;


/**
 * 国际化接口
 */

//各个语言接口函数指针结构体
typedef struct _SCW_LANG_FUNC_T
{ 
    scw_lang_dict_t * (*pfunc_scw_load_lang_dict)(const char* fullpath, scw_conf_section_t* pscwconf_sec); //语言相关scw_load_lang_dict函数指针
    scw_lang_inner_t* (*pfunc_scw_create_lang_inner)(unsigned int tsize, int flag); //语言相关scw_create_lang_inner函数指针
    int (*pfunc_scw_segment_words)(scw_lang_dict_t * pwdict, scw_out_t * pout, const char* inbuf, const int inlen,int langid, void* lang_para); //语言相关scw_segment_words函数指针
    void (*pfunc_scw_destroy_lang_inner)(scw_lang_inner_t *plir); //语言相关scw_destroy_lang_inner函数指针
    void (*pfunc_scw_destroy_lang_dict)(scw_lang_dict_t* ldict); //语言相关scw_destroy_lang_dict函数指针
}scw_lang_func_t;
// 配置文件结构体
typedef struct _SCW_CONF_T
{
    int lang_num;    /**< 可用的语言section数*/
    scw_conf_section_t *lang_section;    /**< 语言section的结构*/
    scw_lang_func_t **ppfunc;    /**< 各个语言接口函数指针*/
    int* langtype2id; /**< 语言转换数组，ccode->conf文件中的langid*/
}scw_conf_t;

extern scw_conf_t* pgconf;
/**
 *读取scw.conf文件，并初始化各个语言的函数指针
 * @param [in] confpath: const char* conf文件路径
 * @param [out]  scw_conf_t* 返回指向scw_conf_t结构的指针
 * -NULL 加载失败
 * -非NULL 加载成功
 * */
scw_conf_t* scw_load_conf(const char* confpath);
/**
 * 加载字典，按着各个语言的配置项进行加载
 * @param [in] dictpath: const char* 字典路径
 * @return 返回字典指针
 * -NULL 字典加载失败
 * -非NULL 字典加载成功，返回字典指针
 * */
scw_worddict_t* scw_load_worddict(const char* dictpath);
/**
 * 线程资源申请，切词输出结构申请
 * @param [in] tsize : unsigned int 申请空间初始化个数
 * @param [in] flag : int 标志位，表明输出时的粒度
 * @return scw_out_t* 输出结构指针
 * -NULL 申请没有成功
 * -非NULL 申请成功
 * */
scw_out_t * scw_create_out(unsigned int tsize, int flag);
/**
 *切词主函数
 *@param [in] pdict: scw_worddict_t* 全局字典结构指针
 *@param [in] pout: scw_out_t * 切词输出结构指针
 *@param [in] inbuf : const char* 切词文本
 *@param [in] inlen : const int 切词长度
 *@param [in] langid : int 切词语言id，在配置文件中指定的id号
 *@param [in] lang_para: void* 切词配置项设置
 *return int 切词是否
 * -1 切词失败
 * 1 切词成功
 * */
int scw_segment_words(scw_worddict_t * pdict,
        scw_out_t * pout,
        const char* inbuf, 
        const int inlen, 
        int langid = LANGTYPE_SIMP_CHINESE, 
        void* lang_para=NULL);
/**
 * 线程资源销毁
 * @param [in] pout:scw_out_t* 要销毁的结构指针
 * @return void
 * */
void scw_destroy_out(scw_out_t* pout);
/**
 * 销毁全局字典
 * @param [in] pdict :scw_worddict_t* 要销毁的字典指针
 * @return void
 * */
void scw_destroy_worddict_without_conf(scw_worddict_t * pdict);
/**
 * 销毁全局字典
 * @param [in] pdict :scw_worddict_t* 要销毁的字典指针
 * @return void
 * */
void scw_destroy_worddict(scw_worddict_t * pdict);
/**
 * 销毁配置文件结构
 * Note: 正常情况下该函数不需要应用方调用
 *       已经在scw_destroy_worddict()中完成
 * @param [in] pConf : scw_conf_t* 要销毁的结构指针
 * @return void
 * */
void scw_destroy_conf(scw_conf_t *pscw_conf);

/*
 * get wordseg version
 * success : length of version str;
 * fail : -1;
 **/
int scw_get_wordseg_version(char *str, int len);

// directly print version
void scw_show_version();

//{{{int scw_get_worddict_version(int langid, scw_worddict_t* pwdict, char *str, int len)
/*
 * 获取指定语言的词典版本
 * param [in] langid : 指定的语言id
 * param [in] pwdict : 词典包
 * param [out] str : 版本串buffer
 * param [out] len : 版本串长度
 * return int
 * -1 获取不成功
 * >0  获取成功
 * */
int scw_get_worddict_version(int langid, scw_worddict_t* pwdict, char *str, int len);

//{{{scw_is_config_lang(int langtype)
/*
 * 功能；判断字典是否在配置文件中配置了，配置了表示支持该语言的切分，否则不支持
 * param[in] langtype: int 传入的语言标示符，定义同ccode的LANGTYPE
 * return true：配置文件已经配置了,false：没有配置该语言或者参数错误了
 * */
bool scw_is_config_lang(int langtype);

//--------------------------------------------------------------------------------//






#endif

