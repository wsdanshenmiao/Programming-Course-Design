/****************************************************************************************
	Filename:		ManagementAPP.h
	Author:			danshenmiao
	Versions:		1.0
	Creation time:	2024.12.19
	Abstract:		主程序，进行数据的初始化、主要逻辑的执行及数据的释放
****************************************************************************************/

#ifndef __MANAGEMENTAPP__H__
#define __MANAGEMENTAPP__H__

#include "DoubleList.h"

/// <summary>
/// 主程序的数据
/// </summary>
typedef struct ManagementAPP {
	DoubleList* m_FoodMenu;					// 菜单
	DoubleList* m_ClientData;			// 用户数据
	DoubleList* m_AdministratorData;	// 管理者数据
	DoubleList* m_OrderData;			// 订单数据
}ManagementAPP;

// public
bool InitManagementAPP(ManagementAPP* app);
int RunManagementAPP(ManagementAPP* app);
void ExitManagementAPP(ManagementAPP* app);


#endif