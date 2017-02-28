/***************************************************************************
 * 
 * Copyright (c) 2011 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file ul_ccode_query_lang.h
 * @author wanghao02(com@baidu.com)
 * @date 2011/07/18 17:30:18
 * @brief 计算指定query的编码和语言情况，给出置信度列表。
 *  
 **/




#ifndef  __UL_CCODE_QUERY_LANG_H_
#define  __UL_CCODE_QUERY_LANG_H_


#include "ul_ullib.h"

#define MAX_RS_NUM 14//输出包，包含14种识别结果
#define CONNECT_TIMEOUT 100000//连接时间
#define CCODE_MAX_ENGPRO 100
#define CCODE_MIN_ENGPRO 0
using namespace std;
#define MAX_QUERY_LEN 10240
#define MAX_QUERY_WORD_LEN 1024



//编码类型的名称，下标是该种编码类型在 ul_ccode.h 的 CODE_T 中的值
extern const char* CODE_STRING[];

//语言类型的名称，下标是该种语言类型在 ul_ccode.h 的 LANG_T 中的值
extern const char* LANG_STRING[];



/**
 * @brief 将越南语小写转换成大写，输入输出均为UTF8格式。输入中包含的大写字母和越南语字母被保留。
 *        使用者应当保证pCapital的容量不小于pLow的容量
 * @param [in] pLow   : 小写越南语
 * @param [in] CapLen : pCapital的容量，字节数
 * @param [out]  pCapital  : 大写越南语
 * @return  int
 * @retval  1:转换成功，0:输入的字符串不是UTF8格式，-1:转换失败.
 * @see
 * @note
 * @author wanghao
 * @date 2011/09/01 02:22:10
**/
int ul_ccode_vilow2capital(unsigned char* pCapital,int CapLen,unsigned char* pLow);

/**
 * @brief 将越南语大写转换成小写，输入输出均为UTF8格式。输入中包含的小写字母和越南语字母被保留。
 *         使用者应当保证pLow的容量不小于pCapital的容量
 * @param [in] pCapital   : 大写越南语
 * @param [in] LowLen: 目标字符串容量，字节数
 * @param [out]  pLow  : 小写越南语
 * @return  int
 * @retval  1:转换成功，0:输入的字符串不是UTF8格式，-1:转换失败.
 * @see
 * @note
 * @author wanghao
 * @date 2011/09/01 02:22:10
**/
int ul_ccode_vicaital2low(unsigned char* pLow,int LowLen,unsigned char* pCapital);

/**
 * @brief 将越南语有音调的字符转成无音调字符，输入中无音调字符，非越南语字符被保留到输出。输入输出均为UTF8格式。
 *
 * @param [in] pTone   : 输入
 * @param [in] NoLen: 目标字符串长度，字节数
 * @param [out]  pNo  : 输出
 * @return  int
 * @retval  1:转换成功，0:输入的字符串不是UTF8格式，-1:转换失败.
 * @see
 * @note
 * @author wanghao
 * @date 2011/09/01 02:22:10
**/
int ul_ccode_vitone2notone(unsigned char* pNo,int NoLen,unsigned char* pTone);



/**
 * 支持的语种: 
 * 中文:GB,UTF8
 * 日文:GB,UTF8,EUCJP,Shift-JIS
 * 阿拉伯语:UTF8,ISO-8859-6,WINDOWS-1256,GB
 * 泰语:UTF8,ISO-8859-11,TIS-620,WINDOWS-874,GB
 * 越南语:UTF8,WINDOWS-1258,GB
 * 英语:CODE_T中所有编码类型
 *
 * @brief query编码和语言识别的总接口函数。query长度大于MAX_QUERY_LEN字节，会发生截断。query最长MAX_QUERY_LEN字节。pRes,pDestPack不可同时为NULL，两者之一可为NULL
 
 * @param [in] queryContent:待检查的字符串
 * @param [out] pDestPack: 存储结果的pack包
 * @param [out] pRes:int型数组，存储结果. MAX_RS_NUM个置信度,每个置信度包含三个信息:编码，语言，置信度值.置信度值是负数，值越大，表明query属于该种编码和语言类型的可能性越大。请根据需要自行获取top n个结果。
                     请保证pRes至少指向MAX_RS_NUM*3*sizeof(int)个字节区域。
     				 pRes,pDestPack不可同时为NULL，两者之一可为NULL。
 * @param [in]szRes:指明pRes数组的大小.当pRes不为NULL时，不能大于MAX_RS_NUM*3,不能小于3.函数实际利用 (szRes/3)*3个元素。
 * @param [in] precodetype:已知query的编码类型，只进行语言识别.默认值为 CODETYPE_UNKNOWN(-2)，即同时进行编码识别和语言识别。
 * @return	bool: false,操作失败；true,成功
 * @retval	 
 * @see
 * @note
 * @author wanghao
 * @date 2011/09/01 02:22:10
**/
bool ul_ccode_query_detect(unsigned char* queryContent,ul_package* pDestPack,int* pRes,int szRes,int precodetype = -2);





#endif  //__QUERY_LANG_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
