/****************************************************************************************
	Filename:		FoodInfo.h
	Author:			danshenmiao
	Versions:		1.0
	Creation time:	2024.12.19
	Finish time:	2024.12.22
	Abstract:
****************************************************************************************/

#ifndef __FOODMENU__H__
#define __FOODMENU__H__

#include "DSMUtil.h"

enum FoodType
{
	VEGETABLE = 0,	// 蔬菜
	MEAT = 1,		// 肉类
	DRINKS = 2,		// 饮料
	DESSERT = 3		// 甜点
};

/// <summary>
/// 菜品结构体，删除菜品时需要查找是否有对应的订单，没有才可删除
/// </summary>
typedef struct FoodInfo {
	size_t m_ID;				// 菜品编号
	char m_Name[20];			// 名称
	enum FoodType m_FoodType;	// 类别
	size_t m_Price;				// 价格
}FoodInfo;

void* CreateFoodInfoData();
int CmpFoodMenuDataByPrice(void* f0, void* f1);
int CmpFoodMenuDataByName(void* food, void* name);
int CmpFoodMenuDataByID(void* food, void* id);

void ShowFoodType();
void PrintFoodMenu(void* pValue, void* pad);
void AddFood(DoubleList* foodList);
void RemoveFood(DoubleList* foodList);
// 用户选择商品
ListNode* SelectFood(DoubleList* foodList);
void SaveFoodInfo(void* pValue, void* operateValue);
void ShowFoodMenu(DoubleList* list);

#endif // !__FOODMENU__H__

