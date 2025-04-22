#ifndef __UTIL__H__
#define __UTIL__H__

#include <string.h>
#include "GlobalVariable.h"

//存放辅助函数

void CleanBuffer();

// 字符串输入检测，输入失败返回true
bool StrInputFailure(int erromes, char* name, size_t size);

// 数字输入检测，输入失败返回true
bool NumInputFailure(int erromes);


void SaveUserinfoFunc(void* pValue, void* operateValue);

//保存账号信息
void SaveUserinfo();

// 保存订单
void SaveOrderFormFunc(void* pValue, void* operateValue);

void SaveOrderForm();

// 保存商品信息
void SaveCommodityFunc(void* pValue, void* operateValue);

void SaveCommodity();


// 打印订单链表
void PrintOrderForm(void* pValue, void* operateValue);

// 打印商品
void PrintCommofity(void* pValue, void* operateValue);

// 打印全部账号信息
void PrintUserAll(void* pValue, void* operateValue);

// 打印账号信息,这里没有显示账号的密码
void PrintUser(void* pValue, void* operateValue);

// 全数字或字母
bool IsAllAlphaNumeric(const char* str, size_t num);

// 全数字
bool IsNumber(const char* str, size_t num);


#endif // !__HELLPFUNC__H__

