#ifndef __GLOBALVARIABLE__H__
#define __GLOBALVARIABLE__H__

#include <stdio.h>
#include <stdbool.h>
#include <memory.h>
#include <malloc.h>
#include "List.h"

//订单结构体
typedef struct OrderForm
{
	size_t m_OrderNumber;		// 订单编号
	size_t m_CommodityNum;		// 商品数量
	size_t m_CommodityPrices;	// 商品价格
	char m_UserName[20];		// 用户名
	char m_UserPhoneNum[20];	// 用户手机号
	char m_CommodityName[20];	// 商品名称
	char m_UserAddress[40];		// 用户地址
	char m_OrderStatus[10];		// 订单状态
}OrderForm;

//用户信息
typedef struct Userinfo
{
	char m_Username[20];		// 用户名
	char m_Password[20];		// 用户密码
	char m_UserPhoneNum[20];	// 用户手机号
	char m_Address[40];			// 地址
	size_t m_Balance;			// 余额
}Userinfo;

// 商品结构体
typedef struct Commodity
{
	char m_CommodityName[20];	// 商品名
	size_t m_CommodityPrices;	// 商品价格
}Commodity;

List* g_OrderForm;				// 订单链表

List* g_Userinfo;					// 用户信息链表 

List* g_Commodity;				// 商品链表


#endif // !__GLOBALVARIABLE__H__

