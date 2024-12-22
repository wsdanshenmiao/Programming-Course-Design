/****************************************************************************************
	Filename:		LoginSystem.h
	Author:			danshenmiao
	Versions:		1.0
	Creation time:	2024.12.20
	Finish time:	2024.12.21
	Abstract:		客户和管理员的登录和注册
****************************************************************************************/


#ifndef __CLIENTLOGIN__H__
#define __CLIENTLOGIN__H__

#include "DoubleList.h"

struct ManagementAPP;

// public

ListNode* ManagementAPPLogin(
	char* fileName,
	DoubleList* infoList,
	void registe(DoubleList*),
	ListNode* findInfo(DoubleList*),
	void saveInfo(void*, void*),
	char* catalogue);

/// <summary>
/// 用户登录及注册
/// </summary>
/// <param name="app"></param>
/// <returns></returns>
ListNode* ClientLogin(struct ManagementAPP* app);
void ClientRegiste(DoubleList* infoList);

/// <summary>
/// 管理员登录及注册
/// </summary>
/// <param name="app"></param>
/// <returns></returns>
ListNode* AdministratorLogin(struct ManagementAPP* app);
void AdministratorRegiste(DoubleList* infoList);

#endif