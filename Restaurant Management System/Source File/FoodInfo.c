#include "FoodInfo.h"

void* CreateFoodInfoData()
{
	FoodInfo* food = MALLOC(FoodInfo);
	if (NULL == food)return NULL;

	return (void*)food;
}

int CmpFoodMenuDataByPrice(void* f0, void* f1)
{
	assert(ASSERTPOINTER(f0) && ASSERTPOINTER(f1));
	size_t price0 = ((FoodInfo*)f0)->m_Price;
	size_t price1 = ((FoodInfo*)f1)->m_Price;
	if (price0 > price1)return 1;
	else if (price0 == price1)return 0;
	else return -1;

}

int CmpFoodMenuDataByName(void* food, void* name)
{
	assert(ASSERTPOINTER(food) && ASSERTPOINTER(name));
	FoodInfo* f = (FoodInfo*)food;
	return strncmp(f->m_Name, (char*)name, sizeof(f->m_Name));
}
