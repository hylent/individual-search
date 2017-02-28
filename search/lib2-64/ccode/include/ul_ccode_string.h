/***************************************************************************
 * 
 * Copyright (c) 2010 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file ul_ccode_string.h
 * @author chenminming(chenminming@baidu.com)
 * @date 2010/09/15 03:53:40
 * @brief 
 *  
 **/

#ifndef  __UL_CCODE_STRING_H_
#define  __UL_CCODE_STRING_H_

// ASCII；GBK；UTF8；GB18030 与ul_ccode.h中类型一致
// enum CODE_T { GB18030 = 1, BIG = 2, UTF8 = 3, JPKR = 4, JIS = 5, SJIS = 6, EUCJP = 7, UTF8JP = 8, ASCII = 9, ISO_8859_1 = 10, EUCKR = 11, UCS2 = 12, GBK, CODE_END};


// ENG 英语；SCH 简体中文；TCH繁体中文；JP 日文；KR 韩文；MAL 马来语；GER 德语；FRA 法文；RUA
// 俄文；IRA 伊朗；TUR 土耳其；ARA 阿拉伯
// enum LANG_T { ENG = 0, SCH = 1, TCH = 2, JP = 3, KR, MAL, GER, FRA, RUA, IRA, TUR, ARA, LANG_END};


/**
 * @brief 为mempool及hashmap做全局初始化
 *
 * @return  int
 * @retval   0：初始化成功；-1：初始化失败
 * @see
 * @note
 * @author chenminming
 * @date 2010/10/28 02:15:02
**/
int ul_ccode_memo_init();

/**
 * @brief 为mempool及hashmap分配内存，每个线程调用一次
 *
 * @return  int
 * @retval   0：内存申请成功；-1：内存申请失败
 * @see
 * @note
 * @author chenminming
 * @date 2010/10/28 02:22:10
**/
int ul_ccode_memo_alloc();

/**
 * @brief 释放每个线程中申请的mempool及hashmap内存
 *
 * @return  int
 * @retval   0
 * @see
 * @note
 * @author chenminming
 * @date 2010/10/28 02:24:24
**/
int ul_ccode_memo_free();

/**
 * @brief mempool及hashmap的全局回收
 *
 * @return  void
 * @retval
 * @see
 * @note
 * @author chenminming
 * @date 2010/10/28 02:33:34
**/
void ul_ccode_memo_del();

/**
 * @brief 查找字符串str1中第1次出现子串str2的位置
 *
 * @param [in] str1   : 待扫描字符串
 * @param [in] str2   : str2-待匹配字符串
 * @param [in] codetype   : 输入字符串的编码类型
 * @return  char* str1中第1次出现str2的位置，若找不到返回空
 * @retval NULL:无匹配子串或者参数错误；非NULL表示第一处匹配的指针
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:26:37
**/
char * ul_ccode_find(const char * str1, const char * str2, int codetype);

/**
 * @brief 指定字符串最大长度，查找字符串str1中第1次出现子串str2的位置
 *
 * @param [in] str1   : const char* 待扫描字符串
 * @param [in] szStr1   : int 字符串1的最大字节长度
 * @param [in] str2   : const char* 模式字符串
 * @param [in] szStr2   : int 字符串2的最大字节长度
 * @param [in] codetype   : int 输入字符串的编码类型
 * @return  char* str1中第1次出现str2的位置，若找不到返回空
 * @retval  NULL:无匹配子串或者参数错误；非NULL:匹配指针 
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:33:50
**/
char * ul_ccode_findn(const char * str1, int szStr1, const char * str2, int szStr2, int codetype);

/**
 * @brief 查找字符串str1中最后出现子串str2的位置
 *
 * @param [in] str1   : const char*待扫描字符串
 * @param [in] str2   : const char*待匹配字符串
 * @param [in] codetype   : int输入字符串的编码类型
 * @return  char* str1中最后出现str2的位置
 * @retval   NULL：无匹配子串或者参数错误；非NULL：匹配指针
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:37:23
**/
char * ul_ccode_ifind(const char * str1, const char * str2, int codetype);

/**
 * @brief 给定字符串最大长度，查找字符串str1中最后出现子串str2的位置
 *
 * @param [in] str1   : const char*  待匹配字符串
 * @param [in] szStr1   : int
 * @param [in] str2   : const char* 待扫描字符串
 * @param [in] szStr2   : int
 * @param [in] codetype   : int 输入字符串的编码类型
 * @return  char* str1中最后出现str2的位置
 * @retval  NULL: 无匹配子串或参数错误；非NULL：匹配子串首指针
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:39:09
**/
char * ul_ccode_ifindn(const char * str1, int szStr1, const char * str2, int szStr2, int codetype);

/**
 * @brief 将输入字符串中所有给定的字符串替换成目标字符串 
 *
 * @param [in] strIn   : const char* 输入字符串
 * @param [out] strOut   : char* 输出字符串
 * @param [in] replaceWord   : const char* 待替换字符串
 * @param [in] newWord   : const char* 被替换后的字符串
 * @param [in] codetype   : int 输入字符串的编码类型
 * @return  int 替换次数
 * @retval  -1:参数错误或内存不足；其它：替换次数 
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:39:37
**/
int ul_ccode_replace(const char * strIn, char * strOut, const char * replaceWord, const char *newWord, int codetype);

/**
 * @brief 给定字符串长度限制，将输入字符串中所有给定的字符串替换成目标字符串
 *
 * @param [in] strIn   : const char* 输入字符串
 * @param [in] szIn   : int 最大扫描字节数
 * @param [out] strOut   : char*  输出字符串
 * @param [in] szOut   : int 最大输出长度,不小于输出字符串实际长度+1
 * @param [in] replaceWord   : const char* 待替换字符串
 * @param [in] newWord   : const char* 被替换后的字符串
 * @param [in] codetype   : int 输入字符串的编码类型
 * @return  int 替换次数
 * @retval   -1：参数错误或内存不足；其它：替换次数
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:39:56
**/
int ul_ccode_replacen(const char * strIn, int szIn, char * strOut, int szOut, const char * replaceWord, const char *newWord, int codetype);

/**
 * @brief 将输入字符串中所有给定的字符替换成目标字符或字符串
 *
 * @param [in] strIn   : const char*  输入字符串
 * @param [out] strOut   : char*
 * @param [in] replaceWord   : const char* 待替换字符如"啊吧吗"
 * @param [in] newWord   : const char* 被替换后的字符或字符串
 * @param [in] codetype   : int 输入字符串的编码类型
 * @return  int 替换次数
 * @retval  -1：参数错误或内存错误；其它：替换次数
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:40:09
**/
int ul_ccode_replace_word(const char * strIn, char * strOut, const char * replaceWord, const char *newWord, int codetype);

/**
 * @brief 给定字符串长度限制，将输入字符串中所有给定的字符替换成目标字符或字符串
 *
 * @param [in] strIn   : const char* 输入字符串
 * @param [in] szIn   : int 输入长度
 * @param [out] strOut   : char*  输出字符串
 * @param [in] szOut   : int 输出长度,不小于输出字符串实际长度+1
 * @param [in] replaceWord   : const char* 待替换字符如"啊吧吗"
 * @param [in] newWord   : const char* 被替换后的字符或字符串
 * @param [in] codetype   : int 输入字符串的编码类型
 * @return  int 
 * @retval  -1：参数错误或内存不足；其它： 替换次数
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:40:19
**/
int ul_ccode_replacen_word(const char * strIn, int szIn, char * strOut, int szOut, const char * replaceWord, const char *newWord, int codetype);

/**
 * @brief 删除字符串首部和尾部的空格
 *
 * @param [in] strIn   : const char*  输入字符串
 * @param [out] strOut   : char* 输出字符串
 * @param [in] codetype   : int 输入字符串的编码类型
 * @return  char* 
 * @retval NULL：参数错误或输入字符串不合法；其它：处理后的字符串指针
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:41:02
**/
char * ul_ccode_trim(const char * strIn, char * strOut, int codetype);

/**
 * @brief 给定长度限制，删除字符串首部和尾部的空格
 *
 * @param [in] strIn   : const char*  输入字符串
 * @param [in] szIn   : int  最大输入长度
 * @param [out] strOut   : char* 输出字符串
 * @param [in] szOut   : int  最大输出长度,不小于输出字符串实际长度+1
 * @param [in] codetype   : int 输入字符串的编码类型
 * @return  char* 
 * @retval  NULL：参数错误或输入字符串不合法；其它：处理后的字符串指针
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:41:10
**/
char * ul_ccode_trimn(const char * strIn, int szIn, char * strOut, int szOut, int codetype);

/**
 * @brief 去除字符串中的空格
 *
 * @param [in] strIn   : const char* 输入字符串
 * @param [out] strOut   : char* 输出字符串
 * @param [in] codetype   : int 输入字符串的编码类型
 * @return  char* 处理后的字符串指针
 * @retval  NULL：无效参数或输入字符串不合法；其它：处理后字符串指针
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:41:18
**/
char * ul_ccode_rmblank(const char * strIn, char * strOut, int codetype);

/**
 * @brief 给定长度限制，去除字符串中的空格 
 *
 * @param [in] strIn   : const char* 输入字符串
 * @param [in] szIn   : int 最大输出长度
 * @param [out] strOut   : char* 输出字符串
 * @param [in] szOut   : int 输出buffer长度,不小于输出字符串实际长度+1
 * @param [in] codetype   : int 输入字符串的编码类型
 * @return  char* 
 * @retval NULL：无效参数或输入串非法；其它：处理后的字符串指针
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:41:22
**/
char * ul_ccode_rmblankn(const char * strIn, int szIn, char * strOut, int szOut, int codetype);

/**
 * @brief 去除字符串中的换行符
 *
 * @param [in] strIn   : const char* 输入字符串
 * @param [out] strOut   : char* 输出字符串
 * @param [in] codetype   : int 输入字符串的编码类型
 * @return  char* 
 * @retval  NULL：无效参数或输入串非法；其它：处理后的字符串指针
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:41:25
**/
char * ul_ccode_chomp(const char * strIn, char * strOut, int codetype);

/**
 * @brief 给定长度限制，去除字符串中的换行符
 *
 * @param [in] strIn   : const char* 输入字符串
 * @param [in] szIn   : int 最大输入长度
 * @param [out] strOut   : char* 输出字符串
 * @param [in] szOut   : int 最大输出长度,不小于输出字符串实际长度+1
 * @param [in] codetype   : int 输入字符串的编码类型
 * @return  char* 
 * @retval  NULL：无效参数或输入串非法或输出buffer不足；其它：处理后的字符串指针
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:41:29
**/
char * ul_ccode_chompn(const char * strIn, int szIn, char * strOut, int szOut, int codetype);

/**
 * @brief 去除字符串中包含的指定字符集中的字符
 *
 * @param [in] strIn   : const char* 输入字符串
 * @param [out] strOut   : char* 输出字符串
 * @param [in] inCharSet   : 判断字符是否满足被删除条件的函数指针
 * @param [in] codetype   : int 输入字符串的编码类型
 * @return  char* 
 * @retval  NULL：无效参数或输入串非法；其它：处理后的字符串指针
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:41:29
**/
char * ul_ccode_remove(const char * strIn, char * strOut, int (*inCharSet)(char*, int), int codetype);

/**
 * @brief 去除字符串中包含的指定字符集中的字符
 *
 * @param [in] strIn   : const char* 输入字符串
 * @param [in] szIn   : 输入字符串最大长度
 * @param [out] strOut   : char* 输出字符串
 * @param [in] szOut   : 输出符串最大长度,不小于输出字符串实际长度+1
 * @param [in] inCharSet   : 判断字符是否满足被删除条件的函数指针
 * @param [in] codetype   : int 输入字符串的编码类型
 * @return  char* 
 * @retval  NULL：无效参数、输入串非法、输出buffer不足；其它：处理后的字符串指针
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:41:29
**/
char * ul_ccode_removen(const char * strIn, int szIn, char * strOut, int szOut, int (*inCharSet)(char*, int), int codetype);

/**
 * @brief 将一个字符串根据指定的分割符集合中的字符进行切分（输入字符串将被修改）
 *
 * @param [in] strIn   : char* 输入字符串
 * @param [out] strOut   : char**  输出各子串指针
 * @param [in] maxStr   : int 最大切分子串数
 * @param [in] splitWord   : const char* 分割符集合
 * @param [in] codetype   : int 输入字符串的编码类型
 * @return  int 
 * @retval NULL：无效参数或输入含乱码：其它：切分成的子串的数目
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:42:13
**/
int ul_ccode_split(char * strIn, char ** strOut, int maxStr, const char * splitWord, int codetype);

/**
 * @brief 遍历字符串，得到当前指针指向的下一字符的长度
 *
 * @param [in] strInput   : const char*
 * @param [out] codetype   : int 编码类型，CODE_T中 1-25，除了标记为 rm 的编码类型都支持
 * @return  int 字符长度
 * @retval  非法字符返回0；合法字符返回字符长度('\0'也返回1)，不支持的编码类型返回0
 * @see 
 * @note 
 * @author chenminming wanghao
 * @date 2010/10/28 17:42:19
**/
int ul_ccode_next(const char * strInput, int codetype);

/**
 * @brief 给定字符串最大字节长度，遍历字符串，得到当前指针指向的下一字符的长度
 *
 * @param [in] strInput   : const char*
 * @param [in] szStr   :  int 当前指针指向的最长字节数
 * @param [in] codetype   : int
 * @return  int 
 * @retval  非法字符返回0；合法字符返回字符长度('\0'也返回1)
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:42:24
**/
int ul_ccode_nextn(const char * strInput, int szStr, int codetype);

/**
 * @brief 比较两个字符串包含的字符集合是否相同，针对纯ASCII字符串
 *
 * @param [in] str1   : const char*
 * @param [in] szStr1   : int
 * @param [in] str2   : const char*
 * @param [in] szStr2   : int
 * @return  int 
 * @retval   1表示字符集相同， 0表示不同
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:42:29
**/
int ul_ccode_include_same_alphaset(const char * str1, int szStr1, const char * str2, int szStr2);

/**
 * @brief 判断两个字符串去除空白符后是否相同，针对ASCII字符串
 *
 * @param [in] str1   : const char*
 * @param [in] szStr1   : int
 * @param [in] str2   : const char*
 * @param [in] szStr2   : int
 * @return  int 
 * @retval   相同返回1，不同返回0
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:42:33
**/
int ul_ccode_only_diff_space(const char * str1, int szStr1, const char * str2, int szStr2);

/**
 * @brief 从字符串结尾进行字符串比较，针对纯ASCII字符串
 *
 * @param [in] str1   : const char*
 * @param [in] szStr1   : int
 * @param [in] str2   : const char*
 * @param [in] szStr2   : int
 * @return  int 
 * @retval   参数错误返回-2；相同返回0；str1倒转后字典序大于str2倒转后，返回1；小于返回-1
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:42:36
**/
int ul_ccode_strcmp_reverse(const char * str1, int szStr1, const char * str2, int szStr2);

/**
 * @brief 获取两个字符串的最长公共子序列
 *
 * @param [in] str1   : const char*
 * @param [in] szStr1   : int
 * @param [in] str2   : const char*
 * @param [in] szStr2   : int
 * @param [out] common   : char* 输出最长公共子序列
 * @param [in] szCommon   : int 最大输出长度,不小于输出字符串实际长度+1
 * @param [in] codetype   : int
 * @return  int 最长公共子串的长度
 * @retval  -1：参数错误或内存不足；其它：最长公共子串长度
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:42:40
**/
int ul_ccode_longest_common_substr(const char * str1, int szStr1, const char * str2, int szStr2, char * common, int szCommon, int codetype);

/**
 * @brief 将字符串src拼接到字符串dest尾部
 *
 * @param [out] dest   : char* 待追加的目标字符串
 * @param [in] szDest   : int 目标字符串buffer长度
 * @param [in] src   : const char* 源字符串
 * @param [in] szSrc   : int 字符串src的buffer长度
 * @return  char* 
 * @retval  NULL：参数无效；其它：拼接后的字符串指针
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:42:47
**/
char * ul_ccode_join(char * dest, int szDest, const char * src, int szSrc);

/**
 * @brief 将一个字符串中给定起始和结束位置的子串取出
 *
 * @param [in] strIn   : const char* 输入字符串
 * @param [in] szStrIn   : int 最大输入长度
 * @param [out] strOut   : char* 输出字符串
 * @param [in] szStrOut   : int 最大输出长度,不小于输出字符串实际长度+1
 * @param [in] start   : int 起始位置，0开始
 * @param [in] length   : int 子串长度
 * @param [in] codetype   : int
 * @return  char* 
 * @retval   NULL：参数无效；其它：输出字符串指针
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:42:51
**/
char * ul_ccode_substr(const char * strIn, int szStrIn, char * strOut, int szStrOut, int start, int length, int codetype);

/**
 * @brief 统计一个字符串中字数，支持中日韩等各种字符
 *
 * @param [in] str   : const char*
 * @param [in] szStr   : int
 * @param [in] codetype   : int
 * @return  int 
 * @retval  -1：无效参数；其它：字数
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:42:55
**/
int ul_ccode_len(const char * str, int szStr, int codetype);

/**
 * @brief  统计一个字符串中不包含空白符的字符串长度
 *
 * @param [in] str   : const char*
 * @param [in] szStr   : int
 * @param [in] codetype   : int
 * @return  int 
 * @retval  -1：输入参数无效；其它：空白符除外的长度
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:42:58
**/
int ul_ccode_len_nospace(const char * str, int szStr, int codetype);

/**
 * @brief 计算两个字符串重复字符的个数
 *
 * @param [in] str1   : const char*
 * @param [in] szStr1   : int
 * @param [in] str2   : const char*
 * @param [in] szStr2   : int
 * @param [in] codetype   : int
 * @return  int 相同字符的个数
 * @retval   -1：输入参数无效；其它：重复字符个数
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:43:01
**/
int ul_ccode_count_overlap(const char * str1, int szStr1, const char * str2, int szStr2, int codetype);

/**
 * @brief 获取字符串中有用字长度，包括汉字，ascii字母和数字
 *
 * @param [in] strIn   : const char*
 * @param [in] szStr   : int
 * @param [in] codetype   : int
 * @return  int 
 * @retval   -1：输入参数无效；其它：汉字，ascii字母和数字个数
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:43:06
**/
int ul_ccode_valid_word_len(const char * strIn, int szStr, int codetype);

/**
 * @brief 统计汉字和ascii字符个数
 *
 * @param [in] strIn   : const char*
 * @param [in] szStr   : int
 * @param [in] codetype   : int
 * @return  int 
 * @retval   -1：输入参数无效；其它：汉字和ascii字符个数
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:43:12
**/
int ul_ccode_word_len(const char * strIn, int szStr, int codetype);

/**
 * @brief 统计字符串1中，在字符串2中出现过的字符个数
 *
 * @param [in] str1   : const char*
 * @param [in] szStr1   : int
 * @param [in] str2   : const char*
 * @param [in] szStr2   : int
 * @param [in] codetype   : int
 * @return  int 
 * @retval   -1：输入参数无效；其它：字符串1中出现在字符串2中的字符个数
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:43:21
**/
int ul_ccode_count_inset(const char * str1, int szStr1, const char * str2, int szStr2, int codetype);

/**
 * @brief 判断一个字符串中是否包含另一字符串中出现过的字符
 *
 * @param [in] str1   : const char* 待识别的字符串
 * @param [in] szStr1   : int
 * @param [in] str2   : const char*
 * @param [in] szStr2   : int 待匹配的字符集合
 * @param [in] codetype   : int
 * @return  int 
 * @retval   -1表示输入参数无效；1表示包含；0表示不包含
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:43:26
**/
int ul_ccode_include(const char * str1, int szStr1, const char * str2, int szStr2, int codetype);

/**
 * @brief 判断一个字符串中是否仅包含另一字符串中出现过的字符
 *
 * @param [in] str1   : const char* 待识别的字符串
 * @param [in] szStr1   : int
 * @param [in] str2   : const char* 待匹配的字符集合
 * @param [in] szStr2   : int
 * @param [in] codetype   : int
 * @return  int 
 * @retval   -1表示输入参数无效；1表示包含；0表示不包含
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:43:39
**/
int ul_ccode_only_include(const char * str1, int szStr1, const char * str2, int szStr2, int codetype);

/**
 * @brief 判断一个字符是否为空白符
 *
 * @param [in] str   : const char*
 * @param [in] codetype   : int
 * @return  int 
 * @retval  -1表示输入参数无效，1表示为空格，0表示非空格
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:43:42
**/
int ul_ccode_isspace(const char * str, int codetype);

/**
 * @brief  判断一个字符是否是标点符号，包括全角符号
 *
 * @param [in] ch   : const char*
 * @param [in] codetype   : int
 * @return  int 
 * @retval   -1表示输入无效，0表示否，1表示是
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:43:45
**/
int ul_ccode_ispunct(const char * ch, int codetype);

/**
 * @brief 判断一个字符是否为不可打印（不可能在文本文件中出现）字符
 *
 * @param [in] ch   : const char*
 * @param [in] codetype   : int
 * @return  int 
 * @retval   -1表示输入无效，1表示是不可见字符，0表示为可见字符
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:43:49
**/
int ul_ccode_isspecial(const char * ch, int codetype);

/**
 * @brief 判断是否是汉字数字"零-十"
 *
 * @param [in] str   : const char*
 * @param [in] codetype   : int
 * @return  int 
 * @retval   -1：输入无效；0：否；1：是
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:43:53
**/
int ul_ccode_is_cn_digit(const char * str, int codetype);

/**
 * @brief 判断当前字符是否是一个独立的汉字
 *
 * @param [in] strIn   : const char*
 * @param [in] codetype   : int
 * @return  int 
 * @retval   -1：输入无效；0：否；1：是
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:43:57
**/
int ul_ccode_is_single_cnchar(const char * strIn, int codetype);

/**
 * @brief 判断一个日本字符是否为片假名
 *
 * @param [in] ch   : const char*
 * @param [in] codetype   : int
 * @return  int 
 * @retval   -1输入无效，0否，1是
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:44:01
**/
int ul_ccode_is_pajm(const char * ch, int codetype);

/**
 * @brief 判断当前字符是否为平假名
 *
 * @param [in] ch   : const char*
 * @param [in] codetype   : int
 * @return  int 
 * @retval   -1输入无效，0否，1是
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:44:03
**/
int ul_ccode_is_pijm(const char * ch, int codetype);


/**
 * @brief 判断输入的第一个字节是否为ASCII的英语字母
 *
 * @param [in] str   : const char*
 * @return  int 
 * @retval   -1输入无效，0否，1是
 * @see 
 * @note 
 * @author wanghao
 * @date 2011/10/18
**/
int ul_ccode_is_EnAscii(const char* ch);

/**
 * @brief 判断输入的前几个字节是否为阿拉伯语,仅支持 utf8，gb18030
 *
 * @param [in] str   : const char*
 * @return  int 
 * @retval   -1输入无效，0否，1是
 * @see 
 * @note 
 * @author wanghao
 * @date 2011/10/18
**/
//int ul_ccode_is_arabic(const char* ch,int codetype);

/**
 * @brief 判断输入的前几个字节是否为泰语，仅支持 utf8，gb18030
 *
 * @param [in] str   : const char*
 * @return  int 
 * @retval   -1输入无效，0否，1是
 * @see 
 * @note 
 * @author wanghao
 * @date 2011/10/18
**/
//int ul_ccode_is_thai(const char* ch,int codetype)


/**
 * @brief 判断输入的前两个字节是否为GB编码的非汉字符号
 *
 * @param [in] str   : const char*
 * @return  int 
 * @retval   -1输入无效，0否，1是
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:44:07
**/
int ul_ccode_is_gb_mark(const char * str);


/**
 * @brief 判断输入的前几个字节是否为特殊符号，支持:gb18030,utf8，以及 中日英
 *
 * @param [in] str   : const char*
 * @param [in] codetype: 编码类型
 * @return  int 
 * @retval   -1输入无效，0否，1是
 * @see 
 * @note 
 * @author wanghao
 * @date 2011/10/18
**/
int ul_ccode_is_mark(const char* str,int codetype);


/**
 * @brief 判断输入的前两个字节是否为GB编码的全角空格，逗号，句号
 *
 * @param [in] str   : const char*
 * @return  int 
 * @retval   -1输入无效，0否，1是
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:44:09
**/
int ul_ccode_is_gb_space(const char * str);

/**
 * @brief 判断输入的前两个字节是否为汉字
 *
 * @param [in] strIn   : const char*
 * @param [in] codetype   : int
 * @return  int 
 * @retval   -1输入无效，0否，1是
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:44:13
**/
int ul_ccode_2bytes_iscn(const char * strIn);

/**
 * @brief  判断输入字符串是否为纯ascii码串
 *
 * @param [in] str   : const char*
 * @param [in] szStr   : int
 * @return  int 
 * @retval   -1输入无效，1表示是，0表示否
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:44:17
**/
int ul_ccode_pure_ascii(const char * str, int szStr);

/**
 * @brief 判断输入字符串是否为纯ASCII数字串
 *
 * @param [in] str   : const char*
 * @param [in] szStr   : int
 * @return  int 
 * @retval   -1输入无效，0否；1是
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:44:20
**/
int ul_ccode_pure_digit(const char * str, int szStr);

/**
 * @brief 指定语言类型，判断输入字符串是否是纯粹该语言串
 *
 * @param [in] str   : const char*
 * @param [in] szStr   : int
 * @param [in] langtype   : int 语言类型（0 ENG 英文；1 SCH 简体中文；2 TCH 繁体中文；3 JP 日文；4 KR 韩文；...）
 * @param [in] codetype   : int
 * @return  int 
 * @retval   -1输入无效；1是；0否
 * @see 
 * @note gb18030四字节部分,CJK A,CJK B同时算作简体中文和繁体中文,简gbk_simp.txt,繁gbk_trd.txt,日gbk_jphanzi.txt,韩gbk_kr.txt
 * @author chenminming
 * @date 2010/10/28 17:44:29
**/
int ul_ccode_pure_lang(const char * str, int szStr, int langtype, int codetype);

/**
 * @brief 判断输入ASCII字符串是否包含英文字母
 *
 * @param [in] str   : const char*
 * @param [in] szStr   : int
 * @return  int 
 * @retval   -1输入无效，0否，1是
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:44:32
**/
int ul_ccode_include_alpha(const char * str, int szStr);

/**
 * @brief 判断输入ASCII字符串是否包含数字
 *
 * @param [in] str   : const char*
 * @param [in] szStr   : int
 * @return  int 
 * @retval   -1输入无效，0否，1是
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:44:34
**/
int ul_ccode_include_digit(const char * str, int szStr);

/**
 * @brief 判断输入ASCII字符串是否包含标点符号
 *
 * @param [in] str   : const char*
 * @param [in] szStr   : int
 * @return  int 
 * @retval   -1输入无效，0否，1是
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:44:36
**/
int ul_ccode_include_punct(const char * str, int szStr);

/**
 * @brief 判断一个字符串中是否包含不可见字符
 *
 * @param [in] str   : const char*
 * @param [in] szStr   : int
 * @param [in] codetype   : int
 * @return  int 
 * @retval   -1表示输入无效，1表示包含，0表示不包含
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:44:40
**/
int ul_ccode_include_special(const char * str, int szStr, int codetype);

/**
 * @brief 判断字符串中是否包含指定语言的字符
 *
 * @param [in] str   : const char*
 * @param [in] szStr   : int
 * @param [in] langtype   : int 二进制表示的每一位表示对应的语言类型（0 ENG 英文；1 SCH 简体中文；2
 * TCH 繁体中文；3 JP 日文；4 KR 韩文；...）如19("10011")，表示判断输入字符串中是否包含英文，中文，韩文；
 * @param [in] codetype   : int
 * @return  int 
 * @retval   -1：输入无效；其它：每一位表示对应的语言类型是否存在
 * @see 
 * @note gb18030四字节部分,CJK A,CJK B同时算作简体中文和繁体中文,简gbk_simp.txt,繁gbk_trd.txt,日gbk_jphanzi.txt,韩gbk_kr.txt
 * @author chenminming
 * @date 2010/10/28 17:44:42
**/
int ul_ccode_include_lang(const char * str, int szStr, int langtype, int codetype);

/**
 * @brief 将输入ASCII字符串中所有大写字母转化为小写
 *
 * @param [in] src   : const char* 输入字符串
 * @param [in] szSrc   : int 最大输入长度
 * @param [out] dest   : char* 输入字符串
 * @param [in] szDest   : int 最大输出长度,不小于输出字符串实际长度+1
 * @return  char* 
 * @retval   NULL：输入参数无效；其它：目标字符串首指针
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:44:45
**/
char * ul_ccode_tolower(const char * src, int szSrc, char * dest, int szDest);

/**
 * @brief 将输入ASCII字符串中所有小写字母转化为大写
 *
 * @param [in] src   : const char* 输入字符串
 * @param [in] szSrc   : int 最大输入长度
 * @param [out] dest   : char* 输出字符串
 * @param [in] szDest   : int 最大输出长度，不小于输出字符串实际长度+1
 * @return  char* 
 * @retval   NULL：输入参数无效；其它：输出字符串首指针
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:44:48
**/
char * ul_ccode_toupper(const char * src, int szSrc, char * dest, int szDest);

/**
 * @brief 将输入字符串中的全角字符转化为半角
 *
 * @param [in] srcIn   : const char* 输入字符串
 * @param [in] szSrc   : int 最大输入长度
 * @param [out] dest   : char* 输出字符串
 * @param [in] szDest   : int  最大输出长度，不小于输出字符串实际长度+1
 * @param [in] codetype   : int
 * @return  char* 
 * @retval   NULL：输入参数无效；其它：输出字符串首指针
 * @see 
 * @note 处理GBK、GB18030以及UTF8编码，其余返回空
 * @author chenminming
 * @date 2010/10/28 17:44:50
**/
char * ul_ccode_tohalf(const char * srcIn, int szSrc, char * dest, int szDest, int codetype);

/**
 * @brief 将输入字符串中的所有全角字符转半角，所有大写字符转小写
 *
 * @param [in] srcIn   : const char* 输入字符串
 * @param [in] szSrc   : int 最大输入长度
 * @param [out] dest   : char* 输出字符串
 * @param [in] szDest   : int  最大输出长度，不小于输出字符串实际长度+1
 * @param [in] codetype   : int
 * @return  char* 
 * @retval   NULL：输入参数无效；其它：输出字符串首指针
 * @see 
 * @note 处理GBK、GB18030以及UTF8编码，其余返回空
 * @author chenminming
 * @date 2010/10/28 17:44:56
**/
char * ul_ccode_half_lower(const char * srcIn, int szSrc, char * dest, int szDest, int codetype);

/**
 * @brief 将输入字符串中所有给定字符替换为对应字符，可由此定制“全角->半角”或“半角->全角”转换
 *
 * @param [in] strIn   : const char* 输入字符串
 * @param [in] szIn   : int 输入长度
 * @param [out] strOut   : char*  输出字符串
 * @param [in] szOut   : int  最大输出长度，不小于输出字符串实际长度+1
 * @param [in] replaceWord   : const char* 待替换全角字符如"～！"
 * @param [in] newWord   : const char* 替换成的字符如"~!"
 * @param [in] codetype   : int 输入字符串的编码类型
 * @return  int 
 * @retval  -1：参数错误或内存不足；其它：替换次数
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:40:19
**/
int ul_ccode_convword(const char * strIn, int szIn, char * strOut, int szOut, const char *
    replaceWord, const char *newWord, int codetype);


/**
 * @brief 找出一个ASCII字符串中数字串开始的位置，并且转化成uint
 *
 * @param [in] strIn   : const char*
 * @param [in] szStr   : int
 * @return  unsigned int 
 * @retval   UINT_MAX：输入参数无效或者整数越界；其它：经过转换的uint
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:45:04
**/
unsigned int ul_ccode_str2uint(const char *strIn, int szStr);

/**
 * @brief 按RFC1738的要求将输入url中所有不可打印字符转义成%XX形式，不重复转义，若原本URL中夹杂部分转义后的表示如%20，则%不重复转义
 *
 * @param [in] src   : const char* 输入url
 * @param [in] szSrc   : int 输入url的buffer长度
 * @param [out] dest   : char* 转义后的字符串
 * @param [in] szDest   : int  最大输出长度，不小于输出字符串实际长度+1
 * @return  char* 
 * @retval   NULL：输入参数无效；其它：转义后字符串首指针
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 17:45:06
**/
char * ul_ccode_convurl(const char * src, int szSrc, char * dest, int szDest);

/**
 * @brief 给出当前ascii字符长度
 *
 * @param [in] str   : const char*
 * @return  int 
 * @retval   合法字符返回1，非法字符返回0
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 19:13:07
**/
inline int ul_ccode_next_ascii(const char* str) 
{

    if((unsigned char)str[0] < 0x80) {
		return 1;
    }
    return 0;

}


/**
 * @brief 给出GBK字符的长度
 *
 * @param [in] str   : const char*
 * @return  int 
 * @retval  非法字符返回0；合法字符返回字符长度('\0'也返回1)
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 19:14:10
**/
inline int ul_ccode_next_gbk(const char* str) 
{
    unsigned char * strIn = (unsigned char *)str;

    if(strIn[0] < 0x80) {
		return 1;
    }
    if(strIn[0] >= 0x81 && strIn[0] <= 0xfe && strIn[1] >= 0x40 && strIn[1] <= 0xFE && strIn[1] != 0x7F) {
		return 2;
    }
    return 0;

}

/**
 * @brief 给出GB18030字符长度
 *
 * @param [in/out] str   : const char*
 * @return  int 
 * @retval  非法字符返回0；合法字符返回字符长度('\0'也返回1) 
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 19:14:59
**/
inline int ul_ccode_next_gb18030(const char* str)
{
    unsigned char * strIn = (unsigned char *)str;

    if(strIn[0] < 0x80) {
		return 1;
    }
    if(strIn[0] >= 0x81 && strIn[0] <= 0xfe && strIn[1] >= 0x40 && strIn[1] <= 0xFE && strIn[1] != 0x7F) {
		return 2;
    }
    if(strIn[0] >= 0x81 && strIn[0] <= 0xfe && strIn[1] >= 0x30 && strIn[1] <= 0x39
        && strIn[2] >= 0x81 && strIn[2] <= 0xfe && strIn[3] >= 0x30 && strIn[3] <= 0x39 ) {
        return 4;
    }
    return 0;
}

/**
 * @brief 给出utf8字符长度
 *
 * @param [in/out] str   : const char*
 * @return  int 
 * @retval   非法字符返回0；合法字符返回字符长度('\0'也返回1)
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 19:15:28
**/
inline int ul_ccode_next_utf8(const char* str)
{
    unsigned char * strIn = (unsigned char *)str;

    if(strIn[0] < 0x80) {
		return 1;
	}
	if(strIn[0] >= 0xC2 && strIn[0] < 0xE0 && strIn[1] >> 6 == 2) {
		return 2;
	}
	if(strIn[0] >> 4 == 14 && strIn[1] >> 6 == 2 && strIn[2] >> 6 == 2
        && (strIn[0] > 0xE0 || strIn[1] >= 0xA0)) {
		return 3;
	}
	if(strIn[0] >> 3 == 30 && strIn[1] >> 6 == 2 && strIn [2] >> 6 == 2 && strIn[3] >> 6 == 2 && 
        strIn[0] <= 0xF4 && (strIn[0] > 0xF0 || strIn[1] >= 0x90) ) {
		return 4;
	}
	return 0;

}

/**
 * @brief 限定buffer长度，给出ascii字符长度
 *
 * @param [in/out] str   : const char*
 * @param [in/out] szStr   : int
 * @return  int 
 * @retval   非法字符返回0；合法字符返回字符长度('\0'也返回1)
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 19:15:44
**/
inline int ul_ccode_nextn_ascii(const char* str, int szStr) 
{

    if(szStr > 0 && (unsigned char)str[0] < 0x80) {
		return 1;
    }
    return 0;

}

/**
 * @brief 限定buffer长度，给出gbk字符长度
 *
 * @param [in/out] str   : const char*
 * @param [in/out] szStr   : int
 * @return  int 
 * @retval   非法字符返回0；合法字符返回字符长度('\0'也返回1)
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 19:16:19
**/
inline int ul_ccode_nextn_gbk(const char* str, int szStr) 
{
    unsigned char * strIn = (unsigned char *)str;

    if(szStr > 0 && strIn[0] < 0x80) {
		return 1;
    }
    if(szStr >= 2 && strIn[0] >= 0x81 && strIn[0] <= 0xfe && strIn[1] >= 0x40 && strIn[1] <= 0xFE && strIn[1] != 0x7F) {
		return 2;
    }
    return 0;

}

/**
 * @brief 限定buffer长度，给出gb18030字符长度
 *
 * @param [in/out] str   : const char*
 * @param [in/out] szStr   : int
 * @return  int 
 * @retval   非法字符返回0；合法字符返回字符长度('\0'也返回1)
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 19:16:35
**/
inline int ul_ccode_nextn_gb18030(const char* str, int szStr)
{
    unsigned char * strIn = (unsigned char *)str;

    if(szStr > 0 && strIn[0] < 0x80) {
		return 1;
    }
    if(szStr >= 2 && strIn[0] >= 0x81 && strIn[0] <= 0xfe && strIn[1] >= 0x40 && strIn[1] <= 0xFE && strIn[1] != 0x7F) {
		return 2;
    }
    if(szStr >= 4 && strIn[0] >= 0x81 && strIn[0] <= 0xfe && strIn[1] >= 0x30 && strIn[1] <= 0x39
        && strIn[2] >= 0x81 && strIn[2] <= 0xfe && strIn[3] >= 0x30 && strIn[3] <= 0x39 ) {
        return 4;
    }
    return 0;
}

/**
 * @brief 限定buffer长度，给出utf8字符长度
 *
 * @param [in/out] str   : const char*
 * @param [in/out] szStr   : int
 * @return  int 
 * @retval   非法字符返回0；合法字符返回字符长度('\0'也返回1)
 * @see 
 * @note 
 * @author chenminming
 * @date 2010/10/28 19:16:51
**/
inline int ul_ccode_nextn_utf8(const char* str, int szStr)
{
    unsigned char * strIn = (unsigned char *)str;

    if(szStr > 0 && strIn[0] < 0x80) {
		return 1;
	}
	if(szStr >= 2 && strIn[0] >= 0xC2 && strIn[0] < 0xE0 && strIn[1] >> 6 == 2) {
		return 2;
	}
	if(szStr >= 3 && strIn[0] >> 4 == 14 && strIn[1] >> 6 == 2 && strIn[2] >> 6 == 2
        && (strIn[0] > 0xE0 || strIn[1] >= 0xA0)) {
		return 3;
	}
	if(szStr >= 4 && strIn[0] >> 3 == 30 && strIn[1] >> 6 == 2 && strIn [2] >> 6 == 2 && strIn[3] >> 6 == 2 && 
        strIn[0] <= 0xF4 && (strIn[0] > 0xF0 || strIn[1] >= 0x90) ) {
		return 4;
	}
	return 0;

}

#endif  //__UL_CCODE_STRING_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
