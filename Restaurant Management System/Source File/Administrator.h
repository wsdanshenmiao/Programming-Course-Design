/****************************************************************************************
	Filename:		Administrator.h
	Author:			danshenmiao
	Versions:		1.0
	Creation time:	2024.12.19
	Abstract:		用于处理管理员相关数据
****************************************************************************************/


#ifndef __ADMINISTRATOR__H__
#define __ADMINISTRATOR__H__

#include "DSMUtil.h"
#include "DoubleList.h"

typedef struct AdministratorInfo {
	size_t m_ID;			// 管理者ID
	char m_Password[20];	// 管理者密码
}AdministratorInfo;

void* CreateAdministratorData();
int CmpAdministratorDataByID(void* ad0, void* ad1);
int CmpAdministratorDataByPassword(void* ad, void* password);

void AdministratorSide(struct ManagementAPP* app);
ListNode* FindAdministratorInfo(DoubleList* infoList);
void SaveAdministratorInfo(void* pValue, void* operateValue);
void AdministratorRegiste(DoubleList* infoList);


#endif
