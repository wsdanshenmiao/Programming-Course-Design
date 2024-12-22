#ifndef __ORDER__H__
#define __ORDER__H__

#include "Client.h"
#include "FoodInfo.h"

struct ManagementAPP;

/// <summary>
/// 订单结构体，包含指向客户的指针和物品的指针
/// </summary>
typedef struct OrderInfo
{
	size_t m_OrderNumber;		// 订单编号
	FoodInfo* m_FoodInfo;		// 所定的物品
	ClientInfo* m_Client;		// 订餐的客户
	char m_OrderStatus[10];		// 订单状态
}OrderInfo;

void* CreateOrderInfoData();
int CmpOrderInfoByClient(void* order0, void* order1);
int CmpOrderInfoByOrderNumber(void* order, void* num);

void OrderDishes(struct ManagementAPP* app, ClientInfo* client);
void ShowOrder(void* pValue, void* pad);
void ShowAllOrder(void* pValue, void* pad);
void ProcessOrder(DoubleList* orderList, char* saveFlieName);

/// <summary>
/// 订单类内含指针，需要先初始化菜单和用户再特别初始化菜单
/// </summary>
/// <param name="pValue"></param>
/// <param name="operateValue"></param>
void SaveOrderInfo(void* pValue, void* operateValue);
bool ReadOrderInfo(struct ManagementAPP* app);

#endif