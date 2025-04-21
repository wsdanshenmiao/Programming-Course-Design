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

int CmpFoodMenuDataByID(void* food, void* id)
{
	assert(ASSERTPOINTER(food) && ASSERTPOINTER(id));
	FoodInfo* f = (FoodInfo*)food;
	size_t newId = *((size_t*)id);
	if (f->m_ID > newId)return 1;
	else if (f->m_ID == newId)return 0;
	else return -1;
}

void ShowFoodType()
{
	printf("**************		0.蔬菜		********************\n");
	printf("**************		1.肉类		********************\n");
	printf("**************		2.饮料		********************\n");
	printf("**************		3.甜点		********************\n");
}

void PrintFoodMenu(void* pValue, void* pad)
{
	assert(ASSERTPOINTER(pValue));

	FoodInfo* food = (FoodInfo*)pValue;
	printf("菜品编号：%lld\n", food->m_ID);
	printf("菜品名称：%s\n", food->m_Name);
	printf("菜品类型：");
	char* foodType = "蔬菜";
	switch (food->m_FoodType)
	{
	case VEGETABLE: {
		foodType = "蔬菜"; break;
	}
	case MEAT: {
		foodType = "肉类"; break;
	}
	case DRINKS: {
		foodType = "饮料"; break;
	}
	case DESSERT: {
		foodType = "甜品"; break;
	}
	default:
		break;
	}
	printf("%s\n", foodType);
	printf("菜品价格：%lld\n\n", food->m_Price);
}

void AddFood(DoubleList* foodList)
{
	ListTraversal(foodList, PrintFoodMenu, NULL);
	size_t id;
	char name[20];
	int type;
	size_t price;
	size_t stock;

	printf("请输入菜品ID：\n");
	int erromes = scanf("%zu", &id);
	CleanInputBuffer();
	if (NumInputFailure(erromes)) {
		printf("输入错误。\n");
		return;
	}
	ListNode* node = ListFindNode(foodList, &id, CmpFoodMenuDataByID);
	if (node != ListEnd(foodList)) {
		printf("已存在改菜品ID。\n");
		return;
	}

	printf("请输入菜品名称：\n");
	erromes = scanf("%s", name);
	CleanInputBuffer();
	if (StrInputFailure(erromes, name, sizeof(name))) {
		printf("输入错误。\n");
		return;
	}
	node = ListFindNode(foodList, name, CmpFoodMenuDataByName);
	if (node != ListEnd(foodList)) {
		printf("已存在改菜品名称。\n");
		return;
	}

	printf("菜品类型：\n");
	printf("0.蔬菜：\t");
	printf("1.肉类：\t");
	printf("2.饮料：\t");
	printf("3.甜品：\n");
	printf("请输入菜品类型：\n");
	erromes = scanf("%d", &type);
	CleanInputBuffer();
	if (NumInputFailure(erromes) || !(0 <= type || type < 4)) {
		printf("输入错误。\n");
		return;
	}

	printf("请输入菜品价格：\n");
	erromes = scanf("%zu", &price);
	CleanInputBuffer();
	if (NumInputFailure(erromes)) {
		printf("输入错误。\n");
		return;
	}

	ListNode* foodNode = ListPushFront(foodList);	//插入对象
	if (NULL == foodNode) {
		return;
	}
	FoodInfo* food = (FoodInfo*)foodNode->m_Data;
	food->m_ID = id;
	food->m_FoodType = (enum FoodType)type;
	food->m_Price = price;
	strncpy(food->m_Name, name, sizeof(food->m_Name));
	printf("添加成功\n");
}

void RemoveFood(DoubleList* foodList)
{
	ListTraversal(foodList, PrintFoodMenu, NULL);

	size_t id;

	printf("请输入要移除菜品的ID：\n");
	int erromes = scanf("%zu", &id);
	CleanInputBuffer();
	if (NumInputFailure(erromes)) {
		printf("输入错误。\n");
		return;
	}

	ListNode* node = ListFindNode(foodList, &id, CmpFoodMenuDataByID);
	if (node == ListEnd(node)) {
		printf("未有此菜品。\n");
	}
	else {
		ListEraseNode(foodList, node);
		printf("移除成功。\n");
	}
}

// 用户选择商品
ListNode* SelectFood(DoubleList* foodList)
{
	printf("请输入菜品名称：\n");
	char name[20];
	int error = scanf("%s", name);
	CleanInputBuffer();
	if (StrInputFailure(error, name, sizeof(name))) {
		printf("输入错误。\n");
		return NULL; // 输入失败时返回 NULL
	}
	ListNode* node = ListFindNode(foodList, name, CmpFoodMenuDataByName);
	if (node == ListEnd(foodList)) {
		printf("未找到该商品。\n"); // 若未找到商品，输出提示
	}
	return node; // 返回找到的商品节点
}

void SaveFoodInfo(void* pValue, void* operateValue)
{
	FILE* pfw = (FILE*)operateValue;
	fwrite(pValue, sizeof(FoodInfo), 1, pfw);
}

void ShowFoodMenu(DoubleList* list)
{
	enum ClientMenu {
		EXIT, Increase, Decrease
	};
	enum ClientMenu select = Increase;

	system("cls");
	ListTraversal(list, PrintFoodMenu, NULL);
	while (select) {
		printf("退出：0，价格由低到高：1，价格由高到低：2\n");
		printf("请选择:");
		scanf("%d", &select);
		CleanInputBuffer();
		system("cls");
		switch (select) {
		case EXIT: {
			break;
		}
		case Increase: {
			ListSortintIncrease(list, CmpFoodMenuDataByPrice);
			ListTraversal(list, PrintFoodMenu, NULL);
			break;
		}
		case Decrease: {
			ListSortintDecrease(list, CmpFoodMenuDataByPrice);
			ListTraversal(list, PrintFoodMenu, NULL);
			break;
		}
		default: {
			printf("输入错误。\n");
			break;
		}
		}
	}
	system("cls");
}
