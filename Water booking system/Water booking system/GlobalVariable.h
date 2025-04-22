#ifndef __GLOBALVARIABLE__H__
#define __GLOBALVARIABLE__H__

#include <stdio.h>
#include <stdbool.h>
#include <memory.h>
#include <malloc.h>
#include "List.h"

//�����ṹ��
typedef struct OrderForm
{
	size_t m_OrderNumber;					// �������
	size_t m_CommodityPrices;				// ��Ʒ�۸�
	size_t m_CommodityNum;					// ��Ʒ����
	size_t m_UndeliverNum;					// δ������
	size_t m_DeliverNum;					// ��������
	char m_UserName[20];					// �û���
	char m_UserPhoneNum[20];				// �û��ֻ���
	char m_CommodityName[20];				// ��Ʒ����
	char m_UserAddress[40];					// �û���ַ
	char m_OrderStatus[10];					// ����״̬
	char m_OrderType[10];					// ��������
}OrderForm;

//�û���Ϣ
typedef struct Userinfo
{
	char m_Username[20];					// �û���
	char m_Password[20];					// �û�����
	char m_UserPhoneNum[20];				// �û��ֻ���
	char m_Address[40];						// ��ַ
	size_t m_Balance;						// ���
}Userinfo;

// ��Ʒ�ṹ��
typedef struct Commodity
{
	char m_CommodityName[20];				// ��Ʒ��
	size_t m_CommodityPrices;				// ��Ʒ�۸�
}Commodity;

List* g_OrderForm;							// ��������

List* g_Userinfo;							// �û���Ϣ���� 

List* g_Commodity;							// ��Ʒ����


#endif // !__GLOBALVARIABLE__H__

