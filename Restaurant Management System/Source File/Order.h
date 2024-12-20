#ifndef __ORDER__H__
#define __ORDER__H__

#include "Client.h"
#include "FoodInfo.h"

/// <summary>
/// 订单结构体，包含指向客户的指针和物品的指针
/// </summary>
typedef struct OrderInfo
{
	size_t m_OrderNumber;		// 订单编号
	FoodInfo* m_FoodInfo;		// 所定的物品
	ClientInfo* m_Client;			// 订餐的客户
	char m_OrderStatus[10];		// 订单状态
}OrderInfo;

void* CreateOrderInfoData();
int CmpOrderInfoByClient(void* order0, void* order1);


#endif