/****************************************************************************************
	Filename:		LoginSystem.h
	Author:			danshenmiao
	Versions:		1.0
	Creation time:	2024.12.20
	Abstract:		客户和管理员的登录和注册
****************************************************************************************/


#ifndef __CLIENTLOGIN__H__
#define __CLIENTLOGIN__H__

#include "DoubleList.h"

struct ManagementAPP;

// public
ListNode* ManagementAPPLogin(
	DoubleList* infoList,
	ListNode* findInfo(DoubleList*),
	char* catalogue);
ListNode* ClientLogin(struct ManagementAPP* app);
ListNode* AdministratorLogin(struct ManagementAPP* app);


#endif