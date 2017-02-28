#ifndef __CCODE_H__
#define __CCODE_H__
#include "ul_iconv.h"
#include "ul_def.h"
#include "ul_ccode_string.h"
#include <vector>


#define	TRBUF_SIZE	512

#define BIG5_NUM	0x3695	//13973

#define BIG5_1LO	0xa1	//161
#define	BIG5_1HI	0xf9	//249
#define BIG5_1NUM	0x59	//89
#define	BIG5_2LO1	0x40	//64
#define	BIG5_2HI1	0x7e	//126
#define	BIG5_2NUM1	0x3f	//63
#define	BIG5_2LO2	0xa1	//161
#define	BIG5_2HI2	0xfe	//254
#define	BIG5_2NUM2	0x5e	//94
#define	BIG5_2NUM	0x9d	//157

#define	GBK_NUM		0x5e02	//24066

#define GBK_1LO		0x81	//129
#define GBK_1HI		0xfe	//254
#define	GBK_1NUM	0x7e	//126
#define	GBK_2LO		0x40	//64
#define	GBK_2HI		0xfe	//254
#define	GBK_2NUM	0xbf	//191
#define GBK_2INV	0x7f	//127


//LANGTYPE_NULL为 新旧ccode的标识，当LANGTYPE被置为此值时说明是旧ccode的识别结果
//LANGTYPE_GLOBAL 表示支持所有语言
//LANGTYOE_END 表示当前语言种类的数目
//最多支持128个(0-127)语种，因为8个字节表示，而且是有符号数
typedef enum _LANG_T {
    LANGTYPE_NULL = -3,//新旧ccode的标识，当LANGTYPE被置为此值时说明是旧ccode的识别结果
    LANGTYPE_NONE = -1,
    LANGTYPE_ENGLISH=0,//英文
    LANGTYPE_SIMP_CHINESE=1,//简体中文
    LANGTYPE_TRAD_CHINESE=2,//繁体中文
    LANGTYPE_JAPANESE=3,//日语
    LANGTYPE_KOREAN=4,//朝鲜语
    LANGTYPE_TURKISH=5,//土耳其语
    LANGTYPE_THAI=6,//泰语
    LANGTYPE_VIETNAMESE=7,//越南语
    LANGTYPE_MALAY=8,//马来语
    LANGTYPE_GERMAN=9,//德语
    LANGTYPE_FRENCH=10,//法语
    LANGTYPE_RUSSIAN=11,//俄语
    LANGTYPE_IRANIAN=12,//伊朗语=波斯语
    LANGTYPE_ARABIC=13,//阿拉伯语
    LANGTYPE_ESTONIAN=14,//爱沙尼亚语
    LANGTYPE_BELARUSIAN=15,//白俄罗斯语
    LANGTYPE_BULGARIAN=16,//保加利亚语
    LANGTYPE_HINDI=17,//印地语
    LANGTYPE_ICELANDIC=18,//冰岛语
    LANGTYPE_POLISH=19,//波兰语
    LANGTYPE_FARSI=20,//波斯语
    LANGTYPE_DANISH=21,//丹麦语
    LANGTYPE_FILIPINO=22,//菲律宾语
    LANGTYPE_FINNISH=23,//芬兰语
    LANGTYPE_DUTCH=24,//荷兰语
    LANGTYPE_CATALAN=25,//加泰罗尼亚语
    LANGTYPE_CZECH=26,//捷克语
    LANGTYPE_CROATIAN=27,//克罗地亚
    LANGTYPE_LATVIAN=28,//拉脱维亚
    LANGTYPE_LITHUANIAN=29,//立陶宛
    LANGTYPE_ROMANIAN=30,//罗马尼亚
    LANGTYPE_AFRIKAANS=31,//南非语
    LANGTYPE_NORWEGIAN=32,//挪威
    LANGTYPE_BRAZILIAN=33,//巴西语=葡萄牙语
    LANGTYPE_PORTUGUESE=34,//葡萄牙
    LANGTYPE_SWEDISH=35,//瑞典
    LANGTYPE_SERBIAN=36,//塞尔维亚
    LANGTYPE_ESPERANTO=37,//世界语
    LANGTYPE_SLOVAK=38,//斯洛伐克
    LANGTYPE_SLOVENE=39,//斯洛文尼亚
    LANGTYPE_SWAHILI=40,//斯瓦希里
    LANGTYPE_UKRAINIAN=41,//乌克兰
    LANGTYPE_SPANISH=42,//西班牙
    LANGTYPE_HEBREW=43,//希伯来文
    LANGTYPE_GREEK=44,//希腊
    LANGTYPE_HUNGARIAN=45,//匈牙利
    LANGTYPE_ARMENIAN=46,//亚美尼亚语
    LANGTYPE_ITALIAN=47,//意大利
    LANGTYPE_INDONESIAN=48,//印度尼西亚
    LANGTYPE_ALBANIAN=49,//阿尔巴尼亚语
    LANGTYPE_AMHARIC=50,//阿姆哈拉语
    LANGTYPE_ASSAMIYA=51,//阿萨姆语
    LANGTYPE_AZERBAIJANI=52,//阿塞拜疆语
    LANGTYPE_BASQUE=53,//巴斯克语
    LANGTYPE_BANGLA=54,//孟加拉语
    LANGTYPE_BOSNIAN=55,//波斯尼亚
    LANGTYPE_GALICIAN=56,//加利西亚语
    LANGTYPE_GEORGIAN=57,//格鲁吉亚语
    LANGTYPE_GUJARATI=58,//古吉拉特语
    LANGTYPE_HAUSA=59,//豪萨语
    LANGTYPE_IGBO=60,//伊博语
    LANGTYPE_INUKTITUT=61,//因纽特语
    LANGTYPE_IRISH=62,//爱尔兰语
    LANGTYPE_ISIZULU=63,//祖鲁语
    LANGTYPE_KANNADA=64,//卡纳达语
    LANGTYPE_KAZAKH=65,//哈萨克语
    LANGTYPE_KYRGYZ=66,//吉尔吉斯语
    LANGTYPE_LUXEMBOURGISH=67,//卢森堡语
    LANGTYPE_MACEDONIAN=68,//马其顿语
    LANGTYPE_MALTESE=69,//马耳他语
    LANGTYPE_MAORI=70,//毛利语
    LANGTYPE_MARATHI=71,//马拉提语
    LANGTYPE_NEPALI=72,//尼泊尔语
    LANGTYPE_ORIYA=73,//奥利亚语
    LANGTYPE_PUNJABI=74,//旁遮普语
    LANGTYPE_QUECHUA=75,//凯楚亚语
    LANGTYPE_SETSWANA=76,//塞茨瓦纳语
    LANGTYPE_SINHALA=77,//僧加罗语
    LANGTYPE_TAMIL=78,//泰米尔语
    LANGTYPE_TATAR=79,//塔塔尔语
    LANGTYPE_TELUGU=80,//泰卢固语
    LANGTYPE_URDU=81,//乌尔都语
    LANGTYPE_UZBEK=82,//乌兹别克语
    LANGTYPE_WELSH=83,//威尔士语
    LANGTYPE_YORUBA=84,//约鲁巴语
    LANGTYPE_GLOBAL, // support all of the languages
    LANGTYPE_END     // current langtype num
} LANG_T;


// CODETYPE_END表示当前编码类型的数目
typedef enum _CODE_T {
    CODETYPE_UNKNOWN = -2,
    CODETYPE_NONE = -1,
    CODETYPE_ENG = 0, //mv to langtype
    CODETYPE_GB = 1,//means gb18030 now
    CODETYPE_BIG5 = 2,
    CODETYPE_UTF8 = 3,
    CODETYPE_JPKR = 4,//rm
    CODETYPE_JIS = 5,// added by jcode
    CODETYPE_SJIS = 6,// added by jcode
    CODETYPE_EUCJP = 7,// added by jcode
    CODETYPE_UTF8JP = 8,//rm
    CODETYPE_ASCII = 9,
    CODETYPE_ISO_8859_1 = 10,
    CODETYPE_EUCKR = 11,
    CODETYPE_UCS2 = 12,
    CODETYPE_GBK = 13,
    CODETYPE_ISO_8859_9 = 14,
    CODETYPE_WIN1254 = 15,
    CODETYPE_IBM857 = 16,
    CODETYPE_MACTURKISH = 17,
    CODETYPE_ISO_8859_3 = 18,
    CODETYPE_ISO_8859_6 = 19,
    CODETYPE_WIN1256 = 20,
    CODETYPE_ISO_8859_11 = 21,
    CODETYPE_WIN874 = 22,
    CODETYPE_TIS620 = 23,
    CODETYPE_VISCII = 24,
    CODETYPE_WIN1258 = 25,
    CODETYPE_END // current codetype num
} CODE_T;



/*
query语言识别的特征
*/
typedef struct _CODELANG_INFO{
    char code_type;//编码类型代码，与 ul_ccode.h 的 CODE_T 一致
    char lang_type;//语言类型代码，与 ul_ccode.h 的 LANG_T 一致
	int trigram_trust;//字符级别的概率值
	int words_trust;//词粒度的概率值
	int TRUST;//编码和语言识别的综合置信度
}CODELANG_INFO;

//容器
using std::vector;
typedef vector<CODELANG_INFO> VEC_CODELANG_INFO;


// 语言类型，用于表明某数据/策略支持的语种（语言属性）
// langmark 的每一位代表是否支持相应语种，最多64*2=128个语种
typedef struct _LangType {
    unsigned long long langmark;//低64bit
    unsigned long long langmark_high;//高 64bit
} LangType;
#define MID_LANGTYPE_NUM 64

#define PY_MAXPAGESIZE 512000
#ifndef u_char
#define u_char		unsigned char
#endif

//============== for ccode_check ccode_check_content exit type =================
//modified to 19 from 23, to avoid redefinition with jcode
#define	MAX_CHECK_EXIT		19
#define	CCODE_CHECK_EXIT_1	1
#define	CCODE_CHECK_EXIT_2	2
#define	CCODE_CHECK_EXIT_3	3
#define	CCODE_CHECK_EXIT_4	4
#define	CCODE_CHECK_EXIT_5	5
#define	CCODE_CHECK_EXIT_6	6
#define	CCODE_CHECK_EXIT_7	7
#define	CCODE_CHECK_EXIT_8	8
#define	CCODE_CHECK_EXIT_9	9
#define	CCODE_CHECK_EXIT_10	10
#define	CCODE_CHECK_EXIT_11	11
#define	CCODE_CHECK_EXIT_12	12
#define	CCODE_CHECK_EXIT_13	13
#define	CCODE_CHECK_EXIT_14	14
#define	CCODE_CHECK_EXIT_15	15
#define	CCODE_CHECK_EXIT_16	16
#define	CCODE_CHECK_EXIT_17	17
#define	CCODE_CHECK_EXIT_18	18
#define	CCODE_CHECK_EXIT_19	19

#define CCODE_CHECK_EXIT_20	20
#define CCODE_CHECK_EXIT_21 21
#define CCODE_CHECK_EXIT_22 22
#define CCODE_CHECK_EXIT_23 23


#define	CCODE_CONT_URLNONE		101
#define	CCODE_CONT_SHORT		102
#define	CCODE_CONT_ENG2GB		103
#define	CCODE_CONT_GBBIG52ENG	104
#define	CCODE_CONT_UTF82NONE	105
#define	CCODE_CONT_NONE2ENG		106
#define	CCODE_CONT_REMAIN		107
#define	CCODE_CONT_UTF82ENG		108

#define CCODE_CONT_NONE2GB		109

//definition for codetype/langtype detection
#define CCODE_BUFFER_SIZE 1024
#define CCODE_MAX_CHARSET_LEN 128
#define CCODE_VALUE_NOT_COMPUTED (-1)
#define CCODE_MAX_SAMPLE_LEN 512
#define CCODE_MAX_DETECT_TRUST 1023//query的最高置信度
#define CCODE_MIN_DETECT_TRUST 0//query的最低置信度
#define CCODE_MAX_LANG_TRUST 100//网页语言识别的最高置信度
#define CCODE_MIN_LANG_TRUST 1//网页语言识别的最低置信度

//#define CCODE_DETECT_DEBUG

//not used
#define CCODE_BYTE_FREQ_ARRAY_SIZE 94
#define CCODE_BYTE_FREQ_OFFSET (0xa1)
#define CCODE_BYTE_FREQ_END (0xfe)


/** 
 * @brief 编码识别接口
 * 
 * @param page 页面字符串，不可为NULL
 * @param url 页面url，不可为NULL
 * @param charset 页面charset字符串，如为NULL则将在page中查找
 * @param content 页面正文，可为NULL
 * @param[out] codetype 编码类型
 * 
 * @return 识别成功返回1，出错返回-1
*/
int ul_ccode_detect_codetype(const char *page, const char* url, const char* charset, const char* content, int *out_type);





/** 
 * @brief 编码识别接口
 * 
 * @param page 页面字符串，不可为NULL
 * @param url 页面url，不可为NULL
 * @param charset 页面charset字符串，如为NULL则将在page中查找
 * @param content 页面正文，可为NULL
 * @param content  codetype 已经辨认的编码类型
 * @param[out] langtype 语言类型
 * @param[out] trustarr  语言置信度数组
 * 
 * @return 识别成功返回1，出错返回-1
*/
int ul_ccode_detect_langtype(const char *page, const char* url, const char* charset, const char* content, int *codetype, int* langtype,int * trustarr=NULL);




//=========================================

/* You should specify the `path' to txt's files in which char-map tables are
 * allocated while using these functions.
 *
 * All tables are lying in path/code directory.
 */

/**
 * @brief ccode加载时的控制flag
 * <ul>FLAG_NOT_SPECIAL_CHAR 空flag，只加载默认功能。使用方式和load结果同ccode3.5.1.2以前。
 * <ul>FLAG_SPECIAL_CHAR 控制ccode繁简转换的行为，置此flag则会对一些词组进行特殊处理，如“瞭望”不会被转为“了望”。使用方式和load结果同ccode3.5.1.2以前。
 * <ul>FLAG_QUERY_DETECT 控制是否加载短串编码识别的词典，如需要用到短串编码识别接口ul_ccode_query_detect(char* query, int query_len)，或者ul_ccode_query_detect(char* query)，需要置此项。使用方式和load结果同ccode3.5.1.2以前。
 * <ul>FLAG_QUERY_LANG_DETECT 控制是否下载query的编码和语言识别所需资源，需要使用 ul_ccode_query_detect(unsigned char* queryContent,ul_package* pDestPack,int* pRes,int szRes)，需置此项。
 * <ul>FLAG_PAGE_LANG_DETECT 控制是否下载网页识别所需资源的标志.
 * <ul>FLAG_ALL_CONV 采用支持任意编码间转换的接口。
 * 
 */
#define FLAG_NOT_SPECIAL_CHAR 0 
#define FLAG_SPECIAL_CHAR 1
#define FLAG_QUERY_DETECT 2
#define FLAG_QUERY_LANG_DETECT 4
#define FLAG_PAGE_LANG_DETECT 8

/**
* @brief  langtype定义
*/
typedef struct _langtype_t
{
	int main_lang : 16;		  /**< 对应位的main_langtype信息       */
	int sec_lang : 16;		  /**< 对应位的sec_langtype信息       */
	int flag : 16;		  /**< 前两语种，是否已计算       */
}langtype_t ;

#define main_lang_flag 0X01
#define sec_lang_flag 0X02


/**
 * @brief 加载ccode data文件
 *
 * @param [in] path   : char* ata文件路径 eg: ./code
 * @param [in] flag   : int ,对load资源进行定制:
 * <ul>FLAG_NOT_SPECIAL_CHAR 空flag，只加载默认功能。使用方式和load结果同ccode3.5.1.2以前。
 * <ul>FLAG_SPECIAL_CHAR 控制ccode繁简转换的行为，置此flag则会对一些词组进行特殊处理，如“瞭望”不会被转为“了望”。使用方式和load结果同ccode3.5.1.2以前。
 * <ul>FLAG_QUERY_DETECT 控制是否加载短串编码识别的词典，如需要用到短串编码识别接口ul_ccode_query_detect(char* query, int query_len)，或者ul_ccode_query_detect(char* query)，需要置此项。使用方式和load结果同ccode3.5.1.2以前。
 * <ul>FLAG_QUERY_LANG_DETECT 控制是否下载query的编码和语言识别所需资源，需要使用 ul_ccode_query_detect(unsigned char* queryContent,ul_package* pDestPack,int* pRes,int szRes)，需置此项。
 * <ul>FLAG_PAGE_LANG_DETECT 控制是否下载网页识别所需资源的标志.
 * @return  int 
 * @retval  成功0 失败-1
 * @see 
 * @author chunq
 * @date 2007/12/12 10:32:09
**/
int ul_ccode_load(char *path , int flag = FLAG_NOT_SPECIAL_CHAR) ;

/**
 * @brief	ccode_conv结构全局初始化. 
 *	在不需要加载ccode词典时，用这个接口替代ul_ccode_load()进行全局初始化。
 * @return  int 
 * @retval	0:初始化成功；-1:初始化失败。   
 * @see 
 * @author jiangling 
 * @date 2009/05/15 17:30:34
**/
int ul_ccode_conv_init();

/*
return codetype
currently: 
it can be 
0: english
1: GBK
2: Big5
3: UTF-8 encoded chinese
-1: Other
*/

int ul_ccode_check_realtext(const char* pstr);
int ul_ccode_check(char *pstr);
int ul_ccode_check_notetype (char *pstr, int *out_type);

/*
check whether the main content of a URL is Chinese and should be indexed
Notice: MUST call ul_trans2gb before sending pTitle & pContent to this function
		old_codetype is the return of ul_ccode_check
return: new codetype
*/
int ul_ccode_check_content
	(const char* pTitle, const char* pContent, const char* pUrl, int old_codetype);
int ul_ccode_check_content_notetype
	(const char* pTitle, const char* pContent, const char* pUrl, int old_codetype, int *out_type);

int ul_ccode_del();

/**
 * @brief ccode_conv结构全局回收函数。 
 *  在不需要用ul_ccode_load()加载ccode词典时，用这个接口替代ul_ccode_del()进行全局回收。
 * @return  void 
 * @author jiangling 
 * @date 2009/05/15 18:01:42
**/
void ul_ccode_conv_del();

 /*=============================================================================
  * Function:        ul_is_tradgbk_str       
  * 
  * Description:     judge whether a string is encoded in traditional gbk
  * 
  * Input:           const char* pstr, the string to be judged, it must be a
  * 				 
  * 				 zero ended string                
  * 
  * Return:          1, traditional gbk string; 0. simple gbk string 
  * 
  *============================================================================*/
int ul_is_tradgbk_str(const char* pstr);

/*
ul_trans2gb
return 0 when success
return -1 when error 
*/
int ul_trans2gb(char *input,char *output, int codetype);


 /*=============================================================================
  * Function:        ul_big5_gbk_str       
  * 
  * Description:     translate big5 encoding string into gbk encoding string
  * 
  * Input:           u_char* psrc, input big5 encoding string 
  *                  int len, the length of the psrc, len<=0, the the lenght 
  *                  will be calculated internally,  but must make sure that 
  *                  psrc ended with '\0';                
  * 
  * Output:          u_char* pDest, buffer to hold the gbk encoding string
  * 
  * Return:          <0, failed; >=0, succeed. the lengh of the input string; 
  * 
  * Others:          the buffer length of pdes must be larger or equal than the length
  * 				 of input string.  ul_ccode_load() must be called before
  * 				 this function.
  *============================================================================*/
int ul_big5_gbk_str(u_char *psrc, u_char *pdes, int len);

int ul_big5_gbi_str(u_char *psrc, u_char *pdes, int len);

 /*=============================================================================
  * Function:        ul_gbk_big5_str       
  * 
  * Description:     translate gbk encoding string into big5 encoding string
  * 
  * Input:           u_char* psrc, input big5 encoding string 
  *                  int len, the length of the psrc, len<=0, the the lenght 
  *                  will be calculated internally,  but must make sure that 
  *                  psrc ended with '\0';                
  * 
  * Output:          u_char* pDest, buffer to hold the gbk encoding string
  * 
  * Return:          <0, failed; >=0, succeed. the lengh of the input string; 
  * 
  * Others:          the buffer length of pdes must be larger or equal than the length
  * 				 of input string.  ul_ccode_load() must be called before
  * 				 this function.
  *============================================================================*/
int ul_gbk_big5_str(u_char *psrc, u_char *pdes, int len);

int ul_gbk_gbi_str(u_char *psrc, u_char *pdes, int len);
int ul_gbi_big5_str(u_char *psrc, u_char *pdes, int len);
int ul_gbi_gbk_str(u_char *psrc, u_char *pdes, int len);


// transfer quanjiao keyboard letter/number/symbol to banjiao 
// this transformation can be made in-place, i.e. szIn == szOut
void ul_trans2bj(const char *szIn, char *szOut);

// transfer some special chinese quanjiao symbols to its corresponding banjiao form
// this transformation can be made in-place, i.e. szIn == szOut
void ul_trans2bj_ext(const char *szIn, char *szOut);

// transfer from uppercase to lower case, for gbk-encoded string
// this transformation can be made in-place, i.e. szIn == szOut
// make sure szOut can be written
void ul_trans2lower(const char *szIn, char *szOut);

/*
obsolete function, use ul_trans2bj/ul_trans2bj_ext/ul_trans2lower instead
* transfer quanjiao to banjiao and upper to lower

int ul_transfer_ch(char *input,char *output);
*/

/*=============================================================================
 * Function:		ul_gbk_to_utf8       
 *
 * Description:		translate gbk encoding string into utf8 encoding string
 *
 * Input:			const char* pSrc, input gbk encoding string 
 * 					const unsigned nDesCnt, the length of the dest buffer
 *
 * Output:			char* pDest, buffer to hold the utf8 encoding string
 *
 * Return:			<0, failed; >0, succeed. the lengh of the utf8 string; 
 *
 * Others:			nDestCnt must be larger than 3/2*strlen(pSrc);
 *
 *============================================================================*/
int ul_gbk_to_utf8(char* pDest, const unsigned nDesCnt, const char* pSrc);

/*=============================================================================
 * Function:		ul_utf8_to_gbk       
 *
 * Description:		translate utf8 encoding string into gbk encoding string
 *
 * Input:			const char* pSrc, input gbk encoding string 
 * 					const unsigned nDesCnt, the length of the dest buffer
 *
 * Output:			char* pDest, buffer to hold the gbk encoding string
 *
 * Return:			<0, failed; >0, succeed. the lengh of the gbk string; 
 *
 * Others:			nDestCnt must be larger than strlen(pSrc);
 *
 *============================================================================*/
int ul_utf8_to_gbk(char* pDest, const unsigned nDesDnt, const char* pSrc);

inline int is_big5( u_char *upstr )
{
	if ( (upstr[0]>=0xa1) && (upstr[0]<=0xf9) &&
	     ( (upstr[1]>=0x40) && (upstr[1]<=0x7e) ||
               (upstr[1]>=0xa1) && (upstr[1]<=0xfe)
	   ) ) {
		return 1;
	}
	else{
		return 0;
	}
}

inline int is_gbk( u_char *pstr )
{
	if ( (pstr[0]>=GBK_1LO) && (pstr[0]<=GBK_1HI) &&
	     (pstr[1]>=GBK_2LO) && (pstr[1]<=GBK_2HI) &&
             (pstr[1]!=GBK_2INV)
	   ) {
		return 1;
	}
	else{
		return 0;
	}
}

inline int is_euckr(u_char* pstr){
	return (pstr[0] >= 0xA1 && pstr[0] <= 0xFE && pstr[1] >= 0xA1 && pstr[1] <= 0xFE) ? 1 : 0;
}


inline int is_gb(u_char* pstr)
{
	if ( (pstr[0]>=0xB0) && (pstr[0]<=0xF7) &&
	     (pstr[1]>=0xA1) && (pstr[1]<=0xFE) ) 
	{
		return 1;
	}
	else{
		return 0;
	}
}

inline int is_big5_str(const char* pstr)
{
	char szContent[1024];
	char* pSrc = (char*) pstr;
	char* pDest = szContent;
	char* pEnd = szContent + 256;
	u_char ch;
	int count = 0,  i, real_count=0;
	short former_word = 0;

	// Get out the double bite words
	while( (ch = *pSrc) != 0 && pSrc[1] ){
		if ( ch <= 0x7f )
			++pSrc;
		else{
			if(*(short*)pSrc != former_word)
				++real_count;
			*pDest++ = ch;
			*pDest++ = pSrc[1];
			former_word= *(short*)pSrc;
			pSrc += 2;
			++count;
		}
        if( pDest >= pEnd )
		   break;
	}
	*pDest = 0;
	//len = pDest - szContent;

	if(count == 0)
		return 0;

	for(i= 0;i<count; i++){
		if(!is_big5((u_char*)&szContent[i]))
			return 0;
		if(!is_gb((u_char*)&szContent[i]))
			return 1;
	}

	// can not judge from code range, make a choice of bigger probability
	return 0;
}

inline int is_gbk_str(const char* pSrc);



/**
 * @brief 初始化中日文编码转换所需的结构ccode_conv_t
 * <p>该结构不是线程安全的，每个子线程需要单独维护一个</p>
 *
 * @param conv 待初始化的转换结构体，不能为NULL
 *
 * @return 成功返回0，出错返回-1
 */
int ul_ccode_conv_open(ccode_conv_t* conv);

/**
 * @brief	线程内ccode初始化函数，每个线程调用一次. 
 * 等同于ul_ccode_conv_open(ccode_conv_t* conv)，但不需要显式传递ccode_conv_t结构.
 * @author	jiangling 
 * @date 2009/05/15 10:13:10
**/
int ul_ccode_conv_open();


/**
 * @brief 关闭中日文编码转换所需的结构
 * <p>该不是线程安全的，每个子线程需要单独维护一个</p>
 *
 * @param conv 待关闭的转换结构体
 *
 * @return 返回0
 */
int ul_ccode_conv_close(ccode_conv_t* conv);

/**
 * @brief	线程内ccode关闭函数.
 * 等同于ul_ccode_conv_close(ccode_conv_t* conv)，但不需要显式传递ccode_conv_t结构.
 * @author	jiangling 
 * @date 2009/05/15 10:12:23
**/
int ul_ccode_conv_close();


/** 
 * @brief 将输入字符串转换成GBI编码
 * <p>目前处理GB18030(GBK) BIG5 UTF8到GBI的转换。其它输入编码类型将直接拷贝</p>
 * 
 * @param input 输入字符串
 * @param output 输出buffer，注意：如果输入编码类型是UTF8，则input和output不可是同一buffer，output大小最好是input的2倍
 * @param outlen 输出buffer大小，当输出buffer写满时将不再继续转换
 * @param codetype 输入的编码类型
 * @param conv 用于做编码转换的结构体，用ul_ccode_conv_open和ul_ccode_conv_close打开和关闭。该结构不是线程安全的，各子线程需要维护单独的结构
 * 
 * @return 转换成功返回0，出错返回-1
 */
int ul_trans2gbi(char *input, char *output, int outlen, int codetype, ccode_conv_t* conv);

int ul_trans2gbi(char *input, char *output, int outlen, int codetype);

/** 
 * @brief 将输入字符串转换成GB18030编码
 * <p>目前处理BIG5 UTF8 JIS SHIFT_JIS EUCJP到GB18030的转换，其它输入编码类型将直接拷贝</p>
 * 
 * @param input 输入字符串
 * @param output 输出buffer，注意：如果输入编码类型是UTF8 JIS SHIFT_JIS EUCJP，则input和output不可是同一buffer，output的大小最好是input的2倍
 * @param outlen 输出buffer大小，当输出buffer写满时将不再继续转换
 * @param codetype 输入的编码类型
 * @param cconv 用于做编码转换的结构体，用ul_ccode_conv_open和ul_ccode_conv_close打开和关闭。该结构不是线程安全的，各子线程需要维护单独的结构
 * 
 * @return 转换成功返回0，出错返回-1
 */
int ul_trans2gb18030(char* input, char* output, int outlen, int codetype, ccode_conv_t* conv);

int ul_trans2gb18030(char* input, char* output, int outlen, int codetype);

/**
 * @brief 判断字符串前4个字节是否在gb18030码域内
 *
 * @param s 输入字符串，可以为NULL
 *
 * @return 是则返回true，NULL或不在则返回false
 */
inline bool ul_is_gb18030_4bytes(const char* s){
	return (s != NULL)
		&& IN_RANGE(s[0], 0x81, 0xFE)
		&& IN_RANGE(s[1], 0x30, 0x39)
		&& IN_RANGE(s[2], 0x81, 0xFE)
		&& IN_RANGE(s[3], 0x30, 0x39);
}

/**
 * @brief 判断字符串前4个字节是否是gb18030-2005的四字节汉字
 *
 * @param s 输入字符串，可以为NULL
 *
 * @return 是则返回true，NULL或不是则返回false
 */
inline bool ul_is_gb18030_4bytes_hanzi(const char* s){
	return (s != NULL)
		&& (IN_RANGE(s[0], 0x81, 0x82) || IN_RANGE(s[0], 0x95, 0x98)) //2 sections
		&& IN_RANGE(s[1], 0x30, 0x39)
		&& IN_RANGE(s[2], 0x81, 0xFE)
		&& IN_RANGE(s[3], 0x30, 0x39);
}

/** 
 * @brief 判断字符串开头是否是合法的GB18030字符，给出字符的字节数
 * 
 * @param s 输入字符串，假定是gb18030编码
 * 
 * @return 字符的字节数
 * 0: 如果输入为NULL或空串
 * 1: 如果输入首字节为ASCII字符
 * 2: 如果输入首2字节为GBK字符，即GB18030的双字节部分
 * 4: 如果输入首4字节为GB18030的四字节部分
 * -1: 如果输入不是合法GB18030字符
 */
int ul_next_gb18030(const char* s);

/** 
 * @brief 判断字符串含GB18030字符个数，包括ascii字符、GB18030双字节、GB18030四字节。不包括非法字符
 * 
 * @param s 输入字符串，假定是GB18030编码
 * 
 * @return GB18030字符个数
 */
int ul_gb18030_len(const char* s);

/** 
 * @brief 判断字符串首两字节是否是GB全角标点
 * <p>包括： 、 。 · ˉ ˇ ¨ 〃 — ～ ‖ … ‘ ’ “ ” 〔 〕〈 〉 《 》 「 」 『 』 〖 〗【 】
 *  ！ ＂ ＃ ￥ ％ ＆ ＇ （ ）＊ ＋ ， － ． ／： ； ＜ ＝ ＞ ？ ［ ＼］ ＾ ＿ ｀｛ ｜ ｝ ￣</p>
 * 
 * @param s 输入字符串，假定是GB18030编码
 * 
 * @return 是返回true，否则返回false
 */
inline bool ul_is_gb_punct(const char* s){
	return (s != NULL) && (((u_char)s[0] == 0xA1 && IN_RANGE((u_char)s[1], 0xA2, 0xBF) && (u_char)s[1] != 0xA9) //punctuation in A1
			|| (IS_GB_SMAEK((u_char*)s) && !IS_GB_1234((u_char*)s) && !IS_GB_ABCD((u_char*)s)));//punctuation in A3
}

/**
 * @brief 初始化gb18030到utf8间的转换所需的iconv_t结构
 * <p>iconv不是线程安全的，每个子线程需要单独维护一个iconv_t结构</p>
 *
 * @param gb18030_utf8 gb18030到utf8的转换结构，如为NULL则不初始化
 * @param utf8_gb18030 utf8到gb18030的转换结构，如为NULL则不初始化
 *
 * @return 成功返回0，出错返回-1
 */
int ul_gb18030_utf8_open(iconv_t* gb18030_utf8, iconv_t* utf8_gb18030);

/**
 * @brief 关闭gb18030到utf8间的转换所需的iconv_t结构
 * <p>iconv不是线程安全的，每个子线程需要单独维护一个iconv_t结构</p>
 *
 * @param gb18030_utf8 gb18030到utf8的转换结构，如为NULL则不处理
 * @param utf8_gb18030 utf8到gb18030的转换结构，如为NULL则不处理
 *
 * @return 返回0
 */
int ul_gb18030_utf8_close(iconv_t* gb18030_utf8, iconv_t* utf8_gb18030);

/** 
 * @brief 将输入的gb18030编码的字符串转换为big5编码
 * <p>对于big5没有的gb18030字符，以两个空格代替。</p>
 * 
 * @param psrc 输入字符串
 * @param pdes 输出字符串，两者可以是同一个buffer，否则请保证输出buffer大小至少跟输入相同
 * @param slen 输入字符串长度，函数至多转换slen个字节，如slen<=0，将转换整个输入
 * 
 * @return 转换成功返回1，出错返回-1
 */
int ul_gb18030_big5_str(u_char* psrc, u_char* pdes, int slen);

/**
 * @brief 将输入的gb18030编码的字符串转换为big5编码
 * <p>对于big5没有的gb18030字符，以两个空格代替。</p>
 *
 * @param psrc 输入字符串
 * @param pdes 输出字符串，两者可以是同一个buffer，否则请保证输出buffer大小至少跟输入相同
 * @param slen 输入字符串长度，函数至多转换slen个字节
 *
 * @return 转换成功返回0，出错返回-1,大于0: 转换失败(以空格代替)的字节数 + 未转换的字节数
 */
int ul_gb18030_big5(u_char* psrc, u_char* pdes, int slen);


/** 
 * @brief 将输入的big5编码的字符串转换成gb18030编码
 * <p>由于big5字符在gbk中都有映射，而gbk是gb18030的子集，所以本函数实际做的是big5->gbk转换</p>
 * 
 * @param psrc 输入字符串
 * @param pdes 输出字符串，两者可以是同一个buffer，否则请保证输出buffer大小至少跟输入相同
 * @param slen 输入字符串长度，函数至多转换slen个字节，如slen<=0，将转换整个输入
 * 
 * @return 转换成功返回1，出错返回-1
 */
int ul_big5_gb18030_str(u_char* psrc, u_char* pdes, int slen);

/**
 * @brief 将输入的big5编码的字符串转换成gb18030编码
 * <p>由于big5字符在gbk中都有映射，而gbk是gb18030的子集，所以本函数实际做的是big5->gbk转换</p>
 *
 * @param psrc 输入字符串
 * @param pdes 输出字符串，两者可以是同一个buffer，否则请保证输出buffer大小至少跟输入相同
 * @param slen 输入字符串长度，函数至多转换slen个字节
 *
 * @return 转换成功返回0，出错返回-1,大于0: 转换失败(以空格代替)的字节数 + 未转换的字节数
 */
int ul_big5_gb18030(u_char* psrc, u_char* pdes, int slen);


/** 
 * @brief 将输入的gb18030编码的字符串转换为简体
 * 
 * @param psrc 输入字符串
 * @param pdes 输出字符串，两者可以是同一个buffer，否则请保证输出buffer大小至少跟输入相同
 * @param slen 输入字符串长度，函数至多转换slen个字节，如slen<=0，将转换整个输入
 * 
 * @return 转换成功返回1，出错返回-1
 */
int ul_gb18030_gbi_str(u_char* psrc, u_char* pdes, int slen);

/** 
 * @brief 将输入的gbi编码的字符串转换成gb18030编码
 * 
 * @param psrc 输入字符串
 * @param pdes 输出字符串，两者可以是同一个buffer，否则请保证输出buffer大小至少跟输入相同
 * @param slen 输入字符串长度，函数至多转换slen个字节，如slen<=0，将转换整个输入
 * 
 * @return 转换成功返回1，出错返回-1
 */
int ul_gbi_gb18030_str(u_char* psrc, u_char* pdes, int slen);

/** 
 * @brief 将gb18030编码的字符串转换为utf8编码
 * <p>遇到转换失败的字符用一个空格代替</p>
 * 
 * @param psrc 输入字符串
 * @param pdes 输出字符串，不可与输入字符串相同，其大小不应小于输入的3/2
 * @param destlen 输出buffer大小，当buffer写满时转换将停止
 * @param gb18030_utf8 对应的iconv_t结构，用ul_gb18030_utf8_open打开，用ul_gb18030_utf8_close关闭，非线程安全
 * 
 * @return 成功返回转换失败的字符数，出错返回-1
 */
int ul_gb18030_utf8_str(char* psrc, char* pdes, int destlen, iconv_t* gb18030_utf8);

int ul_gb18030_utf8_str(char* psrc, char* pdes, int destlen);

/** 
 * @brief 将utf8编码的字符串转换为gb18030编码
 * <p>遇到转换失败的字符时，如果是单字节用一个空格代替，否则用两个空格代替</p>
 * 
 * @param psrc 输入字符串
 * @param pdes 输出字符串，不可与输入字符串相同，其大小不应小于输入的2倍
 * @param destlen 输出buffer大小，当buffer写满时转换将停止
 * @param utf8_gb18030 对应的iconv_t结构，用ul_gb18030_utf8_open打开，用ul_gb18030_utf8_close关闭，非线程安全
 * 
 * @return 成功返回转换失败的字符数，出错返回-1
 */
int ul_utf8_gb18030_str(char* psrc, char* pdes, int destlen, iconv_t* utf8_gb18030);

int ul_utf8_gb18030_str(char* psrc, char* pdes, int destlen);



/** 
 * @brief 编码和语言识别接口
 * 
 * @param page 页面字符串，不可为NULL
 * @param url 页面url，不可为NULL
 * @param charset 页面charset字符串，如为NULL则将在page中查找
 * @param content 页面正文，可为NULL
 * @param[out] codetype 编码类型
 * @param[out] langtype 语言类型
 * 
 * @return 识别成功返回1，出错返回-1
 */
int ul_ccode_detect(const char* page, const char* url, const char* charset, const char* content, int* codetype, int* langtype,int * trustarr=NULL);

/**
 * @brief 日文编码和语言识别接口，直接封装ul_ccode_detect
 *
 * @param page 页面字符串，不可为NULL
 * @param url 页面url，不可为NULL
 * @param charset 页面charset字符串，如为NULL则将在page中查找
 * @param content 页面正文，可为NULL
 * @param[out] out_type 编码类型
 *
 * @return 识别成功返回1，出错返回-1
 */
int ul_jcode_detect(char *page, const char* url, const char* charset, const char* content, int *out_type);

/** 
 * @brief 检测短文本的编码类型，可以是GBK UTF8 或UCS2编码.
 * <p>可以通过配置query_detect.conf来指定某个字符串的编码类型，防止识别错误</p>
 * 
 * @param query 待检查的短文本，长度应该在(1, 102400)范围内
 * @param query_len 待检查的短文本的长度，如不大于0，则默认为strlen(query)
 * 
 * @return 短文本编码类型，CODETYPE_GB CODETYPE_UTF8 CODETYPE_NONE之一，出错也返回-2
 */
int ul_ccode_query_detect(char* query, int query_len);

/** 
 * @brief 检测短文本的编码类型，可以是GBK UTF8 或UCS2编码.
 * <p>可以通过配置query_detect.conf来指定某个字符串的编码类型，防止识别错误</p>
 * 
 * @param query 待检查的短文本，长度应该在(1, 102400)范围内，默认输入中不含有\0，将以strlen作为输入的长度
 * 
 * @return 短文本编码类型，CODETYPE_GB CODETYPE_UTF8 CODETYPE_NONE之一，出错也返回-2
 */
int ul_ccode_query_detect(char* query);

/** 
 * @brief 将输入字符串由UCS2编码转换为GBK编码
 * 
 * @param src 输入字符串，不能为空
 * @param[out] dst 输出buffer
 * @param dstlen 输出buffer大小，不能小于1
 * 
 * @return 输出字符串长度，出错返回-1
 */
int ul_ucs2_gbk_str(char* src, char* dst, int dstlen);
	
/**
 * @brief	获取线程内全局私有的ccode_conv结构 
 * @author jiangling 
 * @date 2009/05/15 10:21:52
**/
ccode_conv_t *get_ccode_conv();

//获取线程全局私有的 VEC_CODELANG_INFO 结构,query编码语言识别时，需要
VEC_CODELANG_INFO*get_ccode_query_lang();



/**
 * @brief  使用htmltree 来提高编码精确度编码识别和语言识别增加两个接口，
      主要是把传入 info结构，改为了与ul_ccode_detect接口类似。 
      把info 结构改为了线程内部数据结构，和ccode_conv_t 一样，为了保持接口不变，
      初始化和销毁的函数放到了ul_ccode_conv_open()和ul_ccode_conv_close()中，不需要init。 
      语言识别增加了  trustarr 数组 用于存放各个语言置信度 。
      但只对编码判定为utf-8和 gb18030时 有用。 
      对每个网页，务必先调用ccode_detect_codetype。然后调用ccode_detect_langtype。
      原有接口与现接口不要混用。ul_ccode_detect可以用，没问题。
      考虑到效率，调用ccode_detect_codetype后再调用ccode_detect_langtype，
      如果参数url不变的话不会再重新计算一次info。
      如果要重新计算，可以传入空字符串""。注意不可传入NULL。会直接返回。
 *
 * @param page 页面字符串，不可为NULL
    @main_content 提取的主要内容，
    @page_content 提取的内容，
 * @param url 页面url，不可为NULL
 * @param charset 页面charset字符串，如为NULL则将在page中查找
 * @param content 页面正文，可为NULL
 * @param[out] codetype 编码类型
 * @param[out] langtype 语言类型
 * @param[out] trustarr    最后一个元素是检测字符编码的缓冲区长度
*  

 */
typedef struct _ccode_page_info_t{
		char *  page;
		char *  main_content;
		char * page_content;
		char * title;
		int len_page;
		int len_main_content;
		int len_page_content;
		int len_title;
}ccode_page_info_t;

int ul_ccode_page_detect(ccode_page_info_t* page_info,const char* url, const char* charset, const char* content, int* codetype, int* langtype,int * trustarr);

/**
 * @brief 由输入语种ID返回其字符串描述
 *
 * @param [in] id   : int 语种ID
 * @return  const char*  输入语种的字符串描述
 * @retval   NULL: 输入不合法；其它：输入语种字符串描述
 * @see 
 * @note 返回指针指向全局字符串，必须为const char *
 * @author chenminming
 * @date 2011/01/05 15:55:35
**/
const char * ul_getlangtype(int id);

 
/**
 * @brief 由输入字符串返回语种ID
 *
 * @param [in] langtypeStr   : const char* 输入字符串
 * @return  int 语种ID
 * @retval   -2：输入非法；其它：输入字符串对应ID
 * @see 
 * @note 
 * @author chenminming
 * @date 2011/01/05 15:59:05
**/
int ul_getlangtype(const char * langtypeStr);

/**
 * @brief 清空某数据/策略的语言属性，用于初始化
 *
 * @param [in] langtype   : LangType * 某数据/策略的语言类型
 * @return  int 成功返回0，否则-1
 * @retval  -1：输入非法；0：成功清空语言属性
 * @see 
 * @note 
 * @author chenminming
 * @date 2011/01/05 16:02:36
**/
int ul_langtype_clean(LangType * langtype);

/**
 * @brief 判断某数据/策略的语言属性是否已清空
 *
 * @param [in] langtype   : LangType* 某数据/策略的语言类型
 * @return  int 判断是否已清空
 * @retval  -1：输入非法；1：本数据/策略已成功清空；0：本数据/策略未清空
 * @see 
 * @note 
 * @author chenminming
 * @date 2011/01/05 16:07:14
**/
int ul_langtype_isclean(LangType * langtype);

/**
 * @brief 用于设置本数据/策略的语言属性，输入整形ID，设置对应语言属性
 *
 * @param [in] langtype   : LangType* 本数据/策略的语言类型
 * @param [in] id   : int 输入语言属性ID
 * @return  int 成功返回0，否则-1
 * @retval  -1：输入非法；0：设置成功
 * @see 
 * @note 
 * @author chenminming
 * @date 2011/01/05 16:11:02
**/
int ul_langtype_set(LangType * langtype, int id);

/**
 * @brief 用于设置本数据/策略的语言属性，输入字符串，设置对应语言属性
 *
 * @param [in] langtype   : LangType* 本数据/策略的语言类型
 * @param [in] langtypeStr   : const char* 输入字符串
 * @return  int 成功返回0，否则-1
 * @retval    -1：输入非法；0：设置成功
 * @see 
 * @note 
 * @author chenminming
 * @date 2011/01/05 16:14:58
**/
int ul_langtype_set(LangType * langtype, const char * langtypeStr);

/**
 * @brief 用于添加本数据/策略的语言属性，输入整形ID，添加对应语言属性
 *
 * @param [in/out] langtype   : LangType*本数据/策略的语言类型
 * @param [in] id   : int 输入语言属性ID
 * @return  int 
 * @retval   成功返回0，否则-1
 * @see 
 * @note 
 * @author chenminming
 * @date 2011/01/27 16:40:02
**/
int ul_langtype_add(LangType * langtype, int id);

/**
 * @brief 用于添加本数据/策略的语言属性，输入字符串，添加对应语言属性
 *
 * @param [in/out] langtype   : LangType*本数据/策略的语言类型
 * @param [in] id   : int 输入语言属性ID
 * @return  int 
 * @retval   成功返回0，否则-1
 * @see 
 * @note 
 * @author chenminming
 * @date 2011/01/27 16:40:02
**/
int ul_langtype_add(LangType * langtype, const char * langtypeStr);

/**
 * @brief 输入ID，去除本数据/策略中对应属性
 *
 * @param [in] langtype   : LangType* 本数据/策略的语言类型
 * @param [in] id   : int 输入整形ID
 * @return  int 成功返回0，否则返回-1
 * @retval  -1:输入非法；0：成功
 * @see 
 * @note 
 * @author chenminming
 * @date 2011/01/05 17:51:05
**/
int ul_langtype_unset(LangType * langtype, int id);
 
/**
 * @brief 输入字符串语种，去除本数据/策略中对应属性
 *
 * @param [in] langtype   : LangType* 本数据/策略的语言类型
 * @param [in] langtypeStr   : const char* 输入语种字符串
 * @return  int 成功返回0，否则-1
 * @retval   -1:输入非法；0：成功
 * @see 
 * @note 
 * @author chenminming
 * @date 2011/01/05 18:07:21
**/
int ul_langtype_unset(LangType * langtype, const char * langtypeStr);

/**
 * @brief 用于获取本数据/策略的语言属性,将langtype中的语言属性赋值给ids,返回语言属性数目
 *
 * @param [in] langtype   : LangType* 本数据/策略的语言属性
 * @param [out] ids   : int* 输出语言属性列表
 * @param [in] n   : int     输出buffer长度
 * @return  int 输出的语言属性的数目
 * @retval  -1:参数非法；其它：语言属性数目
 * @see 
 * @note 
 * @author chenminming
 * @date 2011/01/06 08:58:27
**/
int ul_langtype_get(LangType *langtype, int *ids, int n);

/**
 * @brief 用于判断两个语言类型实例的语言属性是否相同
 *
 * @param [in] langtype1   : LangType* 输入语言类型1
 * @param [in] langtype2   : LangType* 输入语言类型2
 * @return  int 
 * @retval   -1：参数非法；1：两语言类型相同；0：两语言类型不同
 * @see 
 * @note 
 * @author chenminming
 * @date 2011/01/06 09:01:34
**/
int ul_langtype_equal(LangType *langtype1, LangType *langtype2);

/**
 * @brief 用于判断本数据/策略的语言属性是否与目标语言属性兼容,判断某个语言属性是否在属性集合langtype中，LANGTYPE_GLOBAL属性兼容所有id
 *
 * @param [in] langtype   : LangTypes* 本数据/策略的语言类型
 * @param [in] id   : int 目标语言属性
 * @return  int 
 * @retval  -1:参数非法；1：兼容；0：不兼容
 * @see 
 * @note 
 * @author chenminming
 * @date 2011/01/06 09:03:03
**/
int ul_langtype_compatible(LangType *langtype, int id);
 
/**
 * @brief 判断多个语言属性是否为langtype的子集
 *
 * @param [in] langtype   : LangType* 本数据/策略语言类型
 * @param [in] id   : int* 目标语言属性列表
 * @param [in] n   : int   语言属性数目
 * @return  int 
 * @retval   -1:参数非法；1：兼容；0：不兼容
 * @see 
 * @note 
 * @author chenminming
 * @date 2011/01/06 09:06:05
**/
int ul_langtype_compatible(LangType *langtype, int *id, int n);

/**
 * @brief 用于判断两个语言类型实例的语言属性是否兼容：langtype2中语言属性是否为langtype1的子集
 *
 * @param [in] langtype1   : LangType* 输入语言类型1
 * @param [in] langtype2   : LangType* 输入语言类型2
 * @return  int 
 * @retval   -1：参数非法；1：兼容；0：不兼容
 * @see 
 * @note 
 * @author chenminming
 * @date 2011/01/06 09:07:46
**/
int ul_langtype_compatible( LangType *langtype1, LangType *langtype2);

/**
 * @brief 用于获取本数据/策略支持的语言属性的数目
 *
 * @param [in] langtype   : LangType* 本数据/策略的语言类型
 * @return  int 返回语言属性数目
 * @retval   -1：参数非法；其它：支持的语言属性数目
 * @see 
 * @note 
 * @author chenminming
 * @date 2011/01/06 09:10:59
**/
int ul_langtype_num( LangType *langtype);

/**
 * @brief 识别输入网页的编码类型,支持UTF8、GB18030、BIG5、EUCKR、EUCJP、SJIS ASCII, ISO-8859-1, WINDOWS-1252; ISO-8859-9, WINDOWS-1254; ISO-8859-6, WINDOWS-1256; TIS-620, WINDOWS-874, ISO-8859-11; WINDOWS-1258
 *
 * @param [in] page   : const char* 输入网页
 * @param [in] url   : const char*  输入url
 * @param [in] charset   : const char* 输入网页charset标记，可为NULL
 * @param [in] content   : const char* 输入正文内容，可为NULL
 * @param [out] codetype   : int* 输出编码类型
 * @return  int
 * @retval -1:参数异常未识别; 0:成功识别为其它类型
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/12/21 20:51:12
**/
int ul_ccode_chardet(const char *page, const char* url, const char* charset, const char* content, int *codetype);

/**
 * @brief 简体中文、繁体中文、日语、英语、土耳其语、阿拉伯语、泰语、越南语、韩语、德语、法语、意大利语、西班牙语、荷兰语
 *
 * @param [in] page   : const char* 输入网页
 * @param [in] url   : const char* 输入网页的url
 * @param [in] charset   : const char* 输入网页的charset标记，可为NULL
 * @param [in] content   : const char* 输入网页正文，可为NULL
 * @param [in/out] codetype   : int* 若编码类型已知，请输入已知的编码类型；否则设置codetype为-2，将自动识别编码类型。
 * @param [out] langtype   : long long* 输出语言类型,为分主语言和次语言,及其置信度。置信度范围为1-100，置信度为0,表示没有计算置信度。该结果直接填充langtype_v2字段。目前，实际最多返回两个语种。
 * @param [out] trustarr   : int* 默认为NULL；trustarr输出现已支持的各种语言的置信度 1-100
 * @return  int
 * @retval   -1：参数异常、未准确识别；0：成功识别为某种语言类型
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/12/19 21:17:33
**/
int ul_ccode_langdet(const char *page, const char* url, const char* charset, const char* content, int *codetype, long long* lang_type, int * trustarr = NULL);

typedef enum _LANG_V2_INDEX{
    V2_MAINLANG = 1,//主语言
    V2_SECLANG = 2,//次语言
    V2_THIRDLANG = 3,//第三语种
    V2_FOURTHLANG = 4,//第四语种
    V2_ALL //全部都返回
} LANG_V2_INDEX;


/**
 * @brief 解析 ul_ccode_langdet语言识别结果,即 百灵 langtype_v2 字段
 *
 * @param [in] v2 : int , ul_ccode_langdet语言识别结果，或者 langtype_v2字段
 * @param [in/out] langtype : int型数组,存储希望返回语种对应的LANG_T
 * @param [in/out] langtype_trust: int型数组,存储希望返回语种的置信度值,可以为NULL。不为NULL时，数组长度必须不小于langtype数组的长度。置信度值范围为1-100
 * @param [in] sz_langtype: int, langtype和langtype_trust数组的长度
 * @param [in] lang_index: int,LANG_V2_INDEX 值,希望返回第几语言.V2_ALL表示全部结果都返回,此时langtype和langtype_trust的结果依次为:主语言，次语言，第三语种等...。默认为V2_MAINLANG,只返回主语言
 * @return  int 实际返回的语种数目
 * @retval  参数错误返回-1，其他:实际返回的语种数目。
 * @see 
 * @note 
 * @author wanghao
 * @date 2012/05/01 11:38:13
**/
int ul_ccode_langtype_v2(long long v2,int* langtype,int* langtype_trust,int sz_langtype,int lang_index = V2_MAINLANG);



/**
 * @brief 返回当前线程的语言类型
 *
 * @return  int 
 * @retval  未成功获取返回-2，其它返回获取的语言类型
 * @see 
 * @note 
 * @author chenminming
 * @date 2011/01/26 11:38:13
**/
int ul_get_globallang();

/**
 * @brief 设置当前线程的语言类型
 *
 * @param [in] langtype   : int 有效范围[LANGTYPE_NONE, LANGTYPE_END)
 * @return  int 
 * @retval  成功设置返回0,失败返回-1
 * @see 
 * @note 
 * @author chenminming
 * @date 2011/01/26 11:42:03
**/
int ul_set_globallang(int langtype);

/**
 * @brief 设置当前进程的全局编码类型
 *
 * @param [in] codetype   : int 有效范围 [CODETYPE_NONE, CODETYPE_END)
 * @return  int 
 * @retval  成功返回0，失败返回-1
 * @see 
 * @note 
 * @author chenminming
 * @date 2011/01/26 12:15:38
**/
int ul_set_globalcode(int codetype);

/**
 * @brief 获取当前进程的全局编码类型
 *
 * @return  int 全局编码类型
 * @retval   
 * @see 
 * @note 
 * @author chenminming
 * @date 2011/01/26 12:45:46
**/
int ul_get_globalcode();

/**
 * @brief 判断输入字符串在GB18030下是否为乱码
 *
 * @param [in] strIn   : char* 输入字符串
 * @param [in] szIn   : int 输入字符串最大长度
 * @return  double
 * @retval  -1:输入非法；其它：乱码字符占输入字符串中有效字符的比例，建议超过0.1时将输入字符串判定为乱码
 * @see 
 * @note 
 * @author chenminming
 * @date 2011/03/01 20:11:45
**/
double ul_ccode_gb_messy(char *strIn, int szIn);



typedef enum _STRING_TYPE{
    FULL_TYPE = 1,//全称
    ABB_TYPE//缩写
} STRING_TYPE;

/**
 * @brief 根据输入的语言类型 LANG_T 值,返回对应的语言字符串
 *
 * @param [in] lang_id   : int LANG_T值
 * @param [in] str_type: STRING_TYPE类型。FULL_TYPE:取语言类型的全称;ABB_TYPE:取iso639-1标准定义的简写,默认是按照全称返回
 * @return  const char* : 对应的 字符串
 * @retval  NULL:输入非法;其他:语言字符串
 * @see 
 * @note 
 * @author wanghao
 * @date 2012/05/01 20:11:45
**/
const char* ul_ccode_getlangtype(int lang_id,STRING_TYPE str_type = FULL_TYPE);


/**
 * @brief 根据输入的语言类型字符串，返回 LANG_T
 *
 * @param [in] str_lang   : const char* 输入字符串
 * @param [in] str_type :  STRING_TYPE类型,指明 str_type是全称还是简写，默认是按照全称返回
 * @return  int : 对应的 LANG_T 值
 * @retval  -2:输入非法;其他:LANG_T值
 * @see 
 * @note 
 * @author wanghao
 * @date 2012/05/01 20:11:45
**/
int ul_ccode_getlangtype(char* str_lang,STRING_TYPE str_type = FULL_TYPE);









#endif
