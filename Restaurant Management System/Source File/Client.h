/****************************************************************************************
	Filename:		Client.h
	Author:			danshenmiao
	Versions:		1.0
	Creation time:	2024.12.19
	Abstract:		用于处理用户相关数据
****************************************************************************************/


#ifndef __CLIENT__H__
#define __CLIENT__H__

#include "DSMUtil.h"
#include"DoubleList.h"

struct ManagementAPP;

typedef struct ClientInfo {
	char m_Clientname[20];		// 用户名
	char m_Password[20];		// 用户密码
	char m_ClientPhoneNum[20];	// 用户手机号
	size_t m_Balance;			// 余额
}ClientInfo;

void* CreateClientData();
int CmpClientDataByBalance(void* c0, void* c1);
int CmpClientDataByPassword(void* client, void* cmpValue);
int CmpClientDataByName(void* client, void* cmpValue);

void ClientSide(struct ManagementAPP* app);
ListNode* FindClientInfo(DoubleList* infoList);
void SaveClientInfo(void* pValue, void* operateValue);
void ClientRegiste(DoubleList* infoList);

#endif