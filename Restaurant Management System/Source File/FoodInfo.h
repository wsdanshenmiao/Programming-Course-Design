#ifndef __FOODMENU__H__
#define __FOODMENU__H__

#include "DSMUtil.h"

enum FoodType
{
	VEGETABLE,	// 蔬菜
	MEAT,		// 肉类
	DRINKS,		// 饮料
	DESSERT		// 甜点
};

/// <summary>
/// 菜品结构体，删除菜品时需要查找是否有对应的订单，没有才可删除
/// </summary>
typedef struct FoodInfo {
	size_t m_ID;				// 菜品编号
	char m_Name[20];			// 名称
	enum FoodType m_FoodType;	// 类别
	size_t m_Price;				// 价格
	size_t m_Stock;				// 库存
}FoodInfo;

void* CreateFoodMenuData();
int CmpFoodMenuDataByPrice(void* f0, void* f1);
int CmpFoodMenuDataByName(void* food, void* name);

#endif // !__FOODMENU__H__

