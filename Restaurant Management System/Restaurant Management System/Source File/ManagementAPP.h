/****************************************************************************************
	Filename:		ManagementAPP.h
	Author:			danshenmiao
	Versions:		1.0
	Creation time:	2024.12.19
	Finish time:	2024.12.22
	Abstract:		主程序，进行数据的初始化、主要逻辑的执行及数据的释放
****************************************************************************************/

#ifndef __MANAGEMENTAPP__H__
#define __MANAGEMENTAPP__H__

#include "DoubleList.h"
#include "DSMUtil.h"

/// <summary>
/// 主程序的数据
/// </summary>
typedef struct ManagementAPP {
	DoubleList* m_FoodData;					// 菜单
	DoubleList* m_ClientData;			// 用户数据
	DoubleList* m_AdministratorData;	// 管理者数据
	DoubleList* m_OrderData;			// 订单数据
	char m_FoodDataFileName[20];
	char m_ClientDataFileName[25];
	char m_AdministratorDataFileName[25];
	char m_OrderDataFileName[25];
}ManagementAPP;

// public
bool InitManagementAPP(ManagementAPP* app);
int RunManagementAPP(ManagementAPP* app);
void ExitManagementAPP(ManagementAPP* app);


#endif