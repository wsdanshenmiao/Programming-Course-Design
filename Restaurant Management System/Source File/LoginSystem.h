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
	ListNode* findInfo(DoubleList*),
	void saveInfo(void*, void*),
	char* catalogue);

/// <summary>
/// 用户登录及注册
/// </summary>
/// <param name="app"></param>
/// <returns></returns>
ListNode* ClientLogin(struct ManagementAPP* app);

/// <summary>
/// 管理员登录及注册
/// </summary>
/// <param name="app"></param>
/// <returns></returns>
ListNode* AdministratorLogin(struct ManagementAPP* app);

/// <summary>
/// 保存信息到文件
/// </summary>
/// <param name="fileName"></param>	文件的名字
/// <param name="infoList"></param>	所要保存的链表
/// <param name="saveInfo"></param>	保存信息的回调函数
void SaveUserInfo(char* fileName, DoubleList* infoList, void saveInfo(void*, void*));

#endif