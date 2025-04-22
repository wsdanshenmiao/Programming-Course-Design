#ifndef __UTIL__H__
#define __UTIL__H__

#include <string.h>
#include "GlobalVariable.h"

//��Ÿ�������

void CleanBuffer();

// �ַ��������⣬����ʧ�ܷ���true
bool StrInputFailure(int erromes, char* name, size_t size);

// ���������⣬����ʧ�ܷ���true
bool NumInputFailure(int erromes);


void SaveUserinfoFunc(void* pValue, void* operateValue);

//�����˺���Ϣ
void SaveUserinfo();

// ���涩��
void SaveOrderFormFunc(void* pValue, void* operateValue);

void SaveOrderForm();

// ������Ʒ��Ϣ
void SaveCommodityFunc(void* pValue, void* operateValue);

void SaveCommodity();


// ��ӡ��������
void PrintOrderForm(void* pValue, void* operateValue);

// ��ӡ��Ʒ
void PrintCommofity(void* pValue, void* operateValue);

// ��ӡȫ���˺���Ϣ
void PrintUserAll(void* pValue, void* operateValue);

// ��ӡ�˺���Ϣ,����û����ʾ�˺ŵ�����
void PrintUser(void* pValue, void* operateValue);

// ȫ���ֻ���ĸ
bool IsAllAlphaNumeric(const char* str, size_t num);

// ȫ����
bool IsNumber(const char* str, size_t num);


#endif // !__HELLPFUNC__H__

