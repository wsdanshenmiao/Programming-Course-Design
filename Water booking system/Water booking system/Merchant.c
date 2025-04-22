#define _CRT_SECURE_NO_WARNINGS

#include "Merchant.h"

#define MALLOC(T) ((T*)malloc(sizeof(T)))


void MerchantCatalogue()
{
	printf("**************   0.返回上一界面   ********************\n");
	printf("**************   1.添加商品       ********************\n");
	printf("**************   2.查看商品       ********************\n");
	printf("**************   3.修改商品信息   ********************\n");
	printf("**************   4.修改订单信息   ********************\n");
	printf("**************   5.删除商品信息   ********************\n");
	printf("**************   6.删除订单信息   ********************\n");
}


// 创建对象
Commodity* NewProduct(const char* name, size_t price)
{
	Commodity* commodity = MALLOC(Commodity);    //malloc返回指针
	if (!commodity) {
		return NULL;
	}
	strncpy(commodity->m_CommodityName, name, sizeof(commodity->m_CommodityName));		//将name的数据赋给结构体中的变量
	commodity->m_CommodityPrices = price;		//将price赋给结构体中对应的变量
	return commodity;
}

// 名字查找函数
bool FindName(void* pValue, void* cmpValue)
{
	Commodity* commodity = (Commodity*)pValue;
	return strncmp(commodity->m_CommodityName, (char*)cmpValue, sizeof((char*)cmpValue)) == 0;
}

// 添加商品
void AddProducts()
{
	printf("请输入商品名称：\n");
	char name[20];
	int erromes = scanf("%s", name);		
	CleanBuffer();
	if (StrInputFailure(erromes, name, sizeof(name))) {
		printf("输入错误。\n");					//erromes存储scanf的返回值，scanf存在返回值0或-1,通过返回值判断输入是否正确
		return;
	}

	printf("请输入商品价格：\n");
	size_t price;
	erromes = scanf("%zu", &price);
	CleanBuffer();
	printf("添加成功\n");
	//printf("是否继续添加\n");
	//printf("0.是\n");
	//printf("1.否\n");
	if (NumInputFailure(erromes)) {				//与字符串检测同理
		printf("输入错误。\n");
		return;
	}
	Commodity* commodity = NewProduct(name, price);	//构造对象
	if (!commodity) {
		return;
	}
	PushFront(g_Commodity, commodity);	//插入新添加的商品信息
}



// 选择修改的商品
Node* ChooseProduct()
{
	printf("请输入要修改商品的名字：\n");
	char name[20];
	int erromes = scanf("%s", name);
	CleanBuffer();
	if (StrInputFailure(erromes, name, sizeof(name))) {
		return NULL;
	}
	return Find(g_Commodity, FindName, name);		//在g_Commodity链表内查找是否存在与name相等的数据
}

// 修改商品
void ModifyProducts()
{
	Node* node = ChooseProduct();			//根据返回值决定下一步操作
	if (!node) {
		printf("未有此商品。\n");
		return;
	}
	//system("cls");
	enum Modify {
		EXIT, NAME, PRICE
	};
	enum Modify select;
	printf("请选择要修改的成员:\n");
	printf("0.取消修改\t\t1.名字\t\t2.价格\n");
	scanf("%d", &select);
	CleanBuffer();
	switch (select) {
	case EXIT: {	// 退出
		break;
	}
	case NAME: {
		printf("请输入新的名字：\n");
		char name[20];
		int erromes = scanf("%s", name);
		CleanBuffer();
		if (StrInputFailure(erromes, name, sizeof(name))) {
			printf("输入错误。\n");
			return;
		}
		Commodity* commodity = (Commodity*)(node->m_Data);			
		strncpy(commodity->m_CommodityName, name, sizeof(commodity->m_CommodityName));
		printf("修改成功。\n");
		break;
	}
	case PRICE: {
		printf("请输入新的价格：\n");
		size_t price;
		int erromes = scanf("%lld", &price);
		CleanBuffer();
		if (NumInputFailure(erromes)) {
			printf("输入错误。\n");
			return;
		}
		((Commodity*)(node->m_Data))->m_CommodityPrices = price;
		printf("修改成功。\n");
		break;
	}
	default: {
		printf("输入错误。\n");
		getchar();
		break;
	}
	}
}

//删除商品
void DelProducts()
{
	printf("请输入要删除商品的名字：\n");
	char name[20];
	int erromes = scanf("%s", name);
	CleanBuffer();
	if (StrInputFailure(erromes, name, sizeof(name))) {
		return NULL;
	}
	Node* node = Find(g_Commodity, FindName, name);
	if (!node) {
		printf("未有此商品。\n");
		return;
	}

	Erase(g_Commodity, node);
	printf("商品已经删除\n");
}


// 查找函数
bool FindOrderForm(void* pValue, void* cmpValue)
{
	OrderForm* orderForm = (OrderForm*)pValue;
	return orderForm->m_OrderNumber == *((size_t*)cmpValue);
}

// 选择订单
Node* ChooseOrderForm()
{
	printf("请输入要管理的订单编号：\n");
	size_t orderNum;
	int erromes = scanf("%zu", &orderNum);
	CleanBuffer();
	if (NumInputFailure(erromes)) {
		return NULL;
	}
	return Find(g_OrderForm, FindOrderForm, &orderNum);
}

// 管理配送状态
void ManageDistribute()
{
	TraversalOperation(g_OrderForm, PrintOrderForm, NULL);
	Node* node = ChooseOrderForm();
	if (!node) {
		printf("未有此订单。\n");
		return;
	}
	enum Modify {
		EXIT, INDELIVERY, HAVEBEENDELIVERED
	};
	enum Modify select;
	printf("请选择要修改的订单状态:\n");
	printf("0.取消修改\t\t1.配送中\t\t2.已送达\n");
	scanf("%d", &select);
	CleanBuffer();
	//system("cls");
	switch (select) {
	case EXIT: {	// 退出
		break;
	}
	case INDELIVERY: {
		strncpy(((OrderForm*)node->m_Data)->m_OrderStatus, "配送中", sizeof("配送中"));
		printf("修改成功。\n");
		break;
	}
	case HAVEBEENDELIVERED: {
		strncpy(((OrderForm*)node->m_Data)->m_OrderStatus, "已送达", sizeof("已送达"));
		printf("修改成功。\n");
		break;
	}
	default: {
		printf("输入错误。\n");
		getchar();
		break;
	}
	}
}

//删除订单
void DelDistribute()
{
	printf("请输入要删除的订单编号：\n");
	size_t orderNum;
	int erromes = scanf("%zu", &orderNum);
	CleanBuffer();
	if (NumInputFailure(erromes)) {
		return NULL;
	}
	Node* node = Find(g_OrderForm, FindOrderForm, &orderNum);
	if (!node) {
		printf("未有此订单。\n");
		return;
	}
	OrderForm* order = (OrderForm*)(node->m_Data);
	if (order->m_UndeliverNum != 0) {
		printf("该订单未配送完。\n");
		return;
	}
	Erase(g_OrderForm, node);
	printf("订单已经删除\n");
}



void MerchantUI()
{
	if (!MerchantLoginUI()) {	//登录失败则退出
		return;
	}
	enum MerchantMenu{
		EXIT,
		ADDPRODUCTS,
		VIEWPRODUCTS,
		MODIFYPRODUCTS,
		MANAGEDISTRIBUTE,
		DELPRODUCTS,
		DELDISTRIBUTE
	};
	enum MasterMenu select;
	do {
		system("cls");
		MerchantCatalogue();	//打印目录
		printf("请选择:");
		scanf("%d", &select);
		CleanBuffer();
		system("cls");
		switch (select) {
		case EXIT: {	// 退出
			SaveCommodity();
			SaveOrderForm();
			break;
		}
		case ADDPRODUCTS: {	// 添加商品
			printf("已存在商品：\n");
			TraversalOperation(g_Commodity, PrintCommofity, NULL);
			AddProducts();
			SaveCommodity();
			getchar();
			break;
		}
		case VIEWPRODUCTS: {	//查看商品
			TraversalOperation(g_Commodity, PrintCommofity, NULL);
			getchar();
			break;
		}
		case MODIFYPRODUCTS: {
			printf("已存在商品：\n");
			TraversalOperation(g_Commodity, PrintCommofity, NULL);
			ModifyProducts();
			SaveCommodity();
			getchar();
			break;
		}
		case MANAGEDISTRIBUTE: {
			ManageDistribute();
			SaveOrderForm();
			getchar();
			break;
		}
		case DELPRODUCTS: {
			printf("已存在商品：\n");
			TraversalOperation(g_Commodity, PrintCommofity, NULL);
			DelProducts();
			SaveCommodity();
			getchar();
			break;
		}
		case DELDISTRIBUTE: {
			TraversalOperation(g_OrderForm, PrintOrderForm, NULL);
			DelDistribute();
			SaveOrderForm();
			getchar();
			break;
		}
		default: {
			printf("输入错误。\n");
			getchar();
			break;
		}
		}
		system("cls");
	} while (select);
}

