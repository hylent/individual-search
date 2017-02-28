/***************************************************************************
 * 
 * Copyright (c) 2011 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file ul_ccode_query_lang.h
 * @author wanghao02(com@baidu.com)
 * @date 2011/07/18 17:30:18
 * @brief ����ָ��query�ı��������������������Ŷ��б�
 *  
 **/




#ifndef  __UL_CCODE_QUERY_LANG_H_
#define  __UL_CCODE_QUERY_LANG_H_


#include "ul_ullib.h"

#define MAX_RS_NUM 14//�����������14��ʶ����
#define CONNECT_TIMEOUT 100000//����ʱ��
#define CCODE_MAX_ENGPRO 100
#define CCODE_MIN_ENGPRO 0
using namespace std;
#define MAX_QUERY_LEN 10240
#define MAX_QUERY_WORD_LEN 1024



//�������͵����ƣ��±��Ǹ��ֱ��������� ul_ccode.h �� CODE_T �е�ֵ
extern const char* CODE_STRING[];

//�������͵����ƣ��±��Ǹ������������� ul_ccode.h �� LANG_T �е�ֵ
extern const char* LANG_STRING[];



/**
 * @brief ��Խ����Сдת���ɴ�д�����������ΪUTF8��ʽ�������а����Ĵ�д��ĸ��Խ������ĸ��������
 *        ʹ����Ӧ����֤pCapital��������С��pLow������
 * @param [in] pLow   : СдԽ����
 * @param [in] CapLen : pCapital���������ֽ���
 * @param [out]  pCapital  : ��дԽ����
 * @return  int
 * @retval  1:ת���ɹ���0:������ַ�������UTF8��ʽ��-1:ת��ʧ��.
 * @see
 * @note
 * @author wanghao
 * @date 2011/09/01 02:22:10
**/
int ul_ccode_vilow2capital(unsigned char* pCapital,int CapLen,unsigned char* pLow);

/**
 * @brief ��Խ�����дת����Сд�����������ΪUTF8��ʽ�������а�����Сд��ĸ��Խ������ĸ��������
 *         ʹ����Ӧ����֤pLow��������С��pCapital������
 * @param [in] pCapital   : ��дԽ����
 * @param [in] LowLen: Ŀ���ַ����������ֽ���
 * @param [out]  pLow  : СдԽ����
 * @return  int
 * @retval  1:ת���ɹ���0:������ַ�������UTF8��ʽ��-1:ת��ʧ��.
 * @see
 * @note
 * @author wanghao
 * @date 2011/09/01 02:22:10
**/
int ul_ccode_vicaital2low(unsigned char* pLow,int LowLen,unsigned char* pCapital);

/**
 * @brief ��Խ�������������ַ�ת���������ַ����������������ַ�����Խ�����ַ�����������������������ΪUTF8��ʽ��
 *
 * @param [in] pTone   : ����
 * @param [in] NoLen: Ŀ���ַ������ȣ��ֽ���
 * @param [out]  pNo  : ���
 * @return  int
 * @retval  1:ת���ɹ���0:������ַ�������UTF8��ʽ��-1:ת��ʧ��.
 * @see
 * @note
 * @author wanghao
 * @date 2011/09/01 02:22:10
**/
int ul_ccode_vitone2notone(unsigned char* pNo,int NoLen,unsigned char* pTone);



/**
 * ֧�ֵ�����: 
 * ����:GB,UTF8
 * ����:GB,UTF8,EUCJP,Shift-JIS
 * ��������:UTF8,ISO-8859-6,WINDOWS-1256,GB
 * ̩��:UTF8,ISO-8859-11,TIS-620,WINDOWS-874,GB
 * Խ����:UTF8,WINDOWS-1258,GB
 * Ӣ��:CODE_T�����б�������
 *
 * @brief query���������ʶ����ܽӿں�����query���ȴ���MAX_QUERY_LEN�ֽڣ��ᷢ���ضϡ�query�MAX_QUERY_LEN�ֽڡ�pRes,pDestPack����ͬʱΪNULL������֮һ��ΪNULL
 
 * @param [in] queryContent:�������ַ���
 * @param [out] pDestPack: �洢�����pack��
 * @param [out] pRes:int�����飬�洢���. MAX_RS_NUM�����Ŷ�,ÿ�����ŶȰ���������Ϣ:���룬���ԣ����Ŷ�ֵ.���Ŷ�ֵ�Ǹ�����ֵԽ�󣬱���query���ڸ��ֱ�����������͵Ŀ�����Խ���������Ҫ���л�ȡtop n�������
                     �뱣֤pRes����ָ��MAX_RS_NUM*3*sizeof(int)���ֽ�����
     				 pRes,pDestPack����ͬʱΪNULL������֮һ��ΪNULL��
 * @param [in]szRes:ָ��pRes����Ĵ�С.��pRes��ΪNULLʱ�����ܴ���MAX_RS_NUM*3,����С��3.����ʵ������ (szRes/3)*3��Ԫ�ء�
 * @param [in] precodetype:��֪query�ı������ͣ�ֻ��������ʶ��.Ĭ��ֵΪ CODETYPE_UNKNOWN(-2)����ͬʱ���б���ʶ�������ʶ��
 * @return	bool: false,����ʧ�ܣ�true,�ɹ�
 * @retval	 
 * @see
 * @note
 * @author wanghao
 * @date 2011/09/01 02:22:10
**/
bool ul_ccode_query_detect(unsigned char* queryContent,ul_package* pDestPack,int* pRes,int szRes,int precodetype = -2);





#endif  //__QUERY_LANG_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
