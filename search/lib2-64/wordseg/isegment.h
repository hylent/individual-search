/*--------------------------------------------------------------------*
 * Copyright (c) 2007 by Baidu  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
 * Any question and suggestion, contact with sharperdavid@hotmail.com.
 *--------------------------------------------------------------------*/

/*
 * API head file for chinese word segmentation library.
 * Author: David Dai
 * Date: 2007/08/20
 */

#ifndef ISEGMENT_H
#define ISEGMENT_H
#include "scwdef.h"
//#include "scw_com.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* subtoken category */
#define TOK_BASIC 1 /* basic term */
#define TOK_SUBPHR 2 /* sub phrase */
#define TOK_PERNAME 3 /* person name */
#define TOK_NEWWORD 4 /*new word*/

/* define the integer type */
#ifndef INT_TYPE_DEFINED
#define INT_TYPE_DEFINED
typedef signed char  int8_t;
typedef unsigned char  uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
#endif /* INT_TYPE_DEFINED */

/* define the token type */
#ifndef TOKEN_TYPE_DEFINED
#define TOKEN_TYPE_DEFINED
#define TERM_MAX_LEN 256

typedef struct
{  
  /* term info */
  uint32_t length : 8;  /* length of term, not include the '\0' */  
  uint32_t offset : 24; /* offset of term in input text */  
  uint32_t type : 8;    /* type info, e.g. POS tag. 0 is invalid, used in postag, NOT used in wordseg */ 
  uint32_t weight : 24; /* weight of term */

  /* property */
  struct
  {
    uint32_t m_lprop;  /* high 32 bit */
    uint32_t m_hprop;  /* low 32 bit */
  } prop;

  /* dict index */
  long index; /* point to the address of dict item */  

  /* term buffer */
  char buffer[TERM_MAX_LEN];

} token_t;
#endif /* TOKEN_TYPE_DEFINED */

#define MAX_PATH_LENG 512

/*!
 * 将scw_out_t结构转换成token_t结构
 * param [in] pout : scw_out_t* pout结构
 * param [in] type: int 指定输出粒度，一下几个值可以使用"|"连接，取多个结果
 * 	SCW_OUT_BASIC:basic粒度  
 * 	SCW_OUT_WPCOMP：混排粒度 
 * 	SCW_OUT_SUBPH：子短语粒度
 * 	SCW_OUT_HUMANNAME：人名粒度
 * 	SCW_OUT_BOOKNAME：书名粒度
 * 	SCW_OUT_NEWWORD：新词和大粒度 
 * 	SCW_OUT_PROP：输出属性 
 * 	//Note: 要获取混排粒度的属性，就用SCW_OUT_WPCOMP|SCW_OUT_PROP
 * param [out] result : token_t[] 输出结构
 * param [in] max : unsigned 最大token数
 * return int
 * = 0 转化不成功
 * > 0 实际token数
 * */
int scw_get_token_1( scw_out_t* pout, int type, token_t result[], unsigned max );
/*
 * 中文特有，获取介于basic和phrase之间的粒度，拆分大粒度phrase
 * param[in] phrasedict : Sdict_search* phrase词典
 * param[in] pout : scw_out_t* pout输出结构
 * param[out] subtokens: token_t[]
 * param[in] tcnt: int
 * return int
 * */
int seg_split( Sdict_search* phrasedict, scw_out_t* pout, token_t subtokens[], int tcnt );



#ifdef __cplusplus
}
#endif

#endif  /* ISEGMENT_H */

