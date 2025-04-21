#include "Order.h"
#include "ManagementAPP.h"
#include <time.h>

void* CreateOrderInfoData()
{
	OrderInfo* order = MALLOC(OrderInfo);
	if (NULL == order)return NULL;

	return order;
}

int CmpOrderInfoByClient(void* order0, void* order1)
{
	assert(ASSERTPOINTER(order0) && ASSERTPOINTER(order1));
	ClientInfo* c0 = ((OrderInfo*)order0)->m_Client;
	ClientInfo* c1 = ((OrderInfo*)order1)->m_Client;

	if (c0 == c1)return 0;
	else return 1;
}

int CmpOrderInfoByOrderNumber(void* order, void* num)
{
	assert(ASSERTPOINTER(order) && ASSERTPOINTER(num));

	OrderInfo* orderInfo = (OrderInfo*)order;
	size_t orderNum = *((size_t*)num);

	if (orderInfo->m_OrderNumber == orderNum)return 0;
	else return 1;
}

void OrderDishes(ManagementAPP* app, ClientInfo* client)
{
	assert(ASSERTPOINTER(app) && ASSERTPOINTER(client));

	ListTraversal(app->m_FoodData, PrintFoodMenu, NULL);
	ListNode* foodNode = SelectFood(app->m_FoodData);
	if (foodNode == ListEnd(app->m_FoodData))return;
	FoodInfo* food = (FoodInfo*)foodNode->m_Data;

	ListNode* orderNode = ListPushBack(app->m_OrderData); // 创建订单
	if (NULL == orderNode) {
		printf("订单创建失败。\n"); // 如果订单创建失败，输出提示
		return;
	}
	srand((unsigned)time(NULL));
	OrderInfo* order = (OrderInfo*)orderNode->m_Data;
	order->m_Client = client;
	order->m_FoodInfo = food;
	order->m_OrderNumber = rand();  // 随机生成订单号
	strncpy(order->m_OrderStatus, "待制作", sizeof(order->m_OrderStatus));
	printf("订单提交成功！订单号：%zu\n", order->m_OrderNumber); // 输出订单提交成功信息及订单号
}

void ShowOrder(void* pValue, void* clientName)
{
	assert(ASSERTPOINTER(pValue));

	OrderInfo* order = (OrderInfo*)pValue;
	assert(ASSERTPOINTER(order->m_Client) && ASSERTPOINTER(order->m_FoodInfo));

	ClientInfo* client = order->m_Client;
	if (0 == strncmp(client->m_ClientName, (char*)clientName, sizeof(client->m_ClientName))) {
		printf("订单编号：%lld\n", order->m_OrderNumber);
		ShowClientNameAndPhoneNum(order->m_Client, clientName);
		PrintFoodMenu(order->m_FoodInfo, clientName);
		printf("订单状态：%s\n", order->m_OrderStatus);
	}
}

void ShowAllOrder(void* pValue, void* pad)
{
	assert(ASSERTPOINTER(pValue));

	OrderInfo* order = (OrderInfo*)pValue;
	assert(ASSERTPOINTER(order->m_Client) && ASSERTPOINTER(order->m_FoodInfo));

	printf("订单编号：%lld\n", order->m_OrderNumber);
	printf("订单状态：%s\n", order->m_OrderStatus);
	ShowClientNameAndPhoneNum(order->m_Client, pad);
	PrintFoodMenu(order->m_FoodInfo, pad);
}

void ProcessOrder(DoubleList* orderList, char* saveFlieName)
{
	ListTraversal(orderList, ShowAllOrder, NULL);
	printf("请输入要管理的订单编号：\n");
	size_t orderNum;
	int erromes = scanf("%zu", &orderNum);
	CleanInputBuffer();
	if (NumInputFailure(erromes)) {
		return;
	}
	ListNode* node = ListFindNode(orderList, &orderNum, CmpOrderInfoByOrderNumber);
	if (node == ListEnd(orderList)) {
		printf("未有此订单。\n");
		return;
	}
	OrderInfo* order = (OrderInfo*)node->m_Data;

	enum Modify {
		EXIT, INPRODUCTION, MEALWAITING
	};
	enum Modify select;
	printf("请选择要修改的成员:\n");
	printf("0.取消修改\t\t1.制作中\t\t2.待取餐\n");
	scanf("%d", &select);
	CleanInputBuffer();
	system("cls");
	switch (select) {
	case EXIT: {	// 退出
		break;
	}
	case INPRODUCTION: {
		strncpy(order->m_OrderStatus, "制作中", sizeof(order->m_OrderStatus));
		printf("修改成功。\n");
		break;
	}
	case MEALWAITING: {
		strncpy(order->m_OrderStatus, "待取餐", sizeof(order->m_OrderStatus));
		printf("修改成功。\n");
		break;
	}
	default: {
		printf("输入错误。\n");
		break;
	}
	}
}


void SaveOrderInfo(void* pValue, void* pf)
{
	assert(ASSERTPOINTER(pValue));

	OrderInfo* order = (OrderInfo*)pValue;
	assert(ASSERTPOINTER(order->m_Client) && ASSERTPOINTER(order->m_FoodInfo));

	ClientInfo* client = order->m_Client;
	FoodInfo* food = order->m_FoodInfo;
	FILE* pfw = (FILE*)pf;
	fwrite(pValue, sizeof(OrderInfo), 1, pfw);
	fwrite(client->m_ClientName, sizeof(client->m_ClientName), 1, pfw);
	fwrite(&food->m_ID, sizeof(food->m_ID), 1, pfw);
}

bool ReadOrderInfo(ManagementAPP* app)
{
	assert(ASSERTPOINTER(app));

	bool successRead = true;;
	char* fileName = app->m_OrderDataFileName;
	FILE* pfr = _access(fileName, 0) ? fopen(fileName, "wb") : fopen(fileName, "rb");;
	void* value = CreateOrderInfoData();
	char name[20];
	size_t id;
	if (NULL == value) {
		return false;
	}
	for (; fread(value, sizeof(OrderInfo), 1, pfr); ) {
		fread(name, sizeof(name), 1, pfr);
		fread(&id, sizeof(size_t), 1, pfr);
		ListNode* node = ListPushBack(app->m_OrderData);
		memcpy(node->m_Data, value, sizeof(OrderInfo));

		OrderInfo* order = (OrderInfo*)node->m_Data;
		node = ListFindNode(app->m_ClientData, name, CmpClientDataByName);
		if (node == ListEnd(app->m_ClientData)) {
			successRead = false;
			break;
		}
		order->m_Client = (ClientInfo*)node->m_Data;

		node = ListFindNode(app->m_FoodData, &id, CmpFoodMenuDataByID);
		if (node == ListEnd(app->m_FoodData)) {
			successRead = false;
			break;
		}
		order->m_FoodInfo = (FoodInfo*)node->m_Data;
	}
	free(value);
	value = NULL;
	fclose(pfr);
	return successRead;
}