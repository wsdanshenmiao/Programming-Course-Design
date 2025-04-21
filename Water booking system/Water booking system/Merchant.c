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
}

// 打印商品链表
void PrintProducts(void* pValue, void* operateValue)
{
	Commodity* commodity = (Commodity*)pValue;
	printf("%s\t%zu\n", commodity->m_CommodityName, commodity->m_CommodityPrices);
}

// 创建对象
Commodity* NewProduct(const char* name, size_t price)
{
	Commodity* commodity = MALLOC(Commodity);
	if (!commodity) {
		return NULL;
	}
	strncpy(commodity->m_CommodityName, name, sizeof(name));
	commodity->m_CommodityPrices = price;
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
		printf("输入错误。\n");
		return;
	}

	printf("请输入商品价格：\n");
	size_t price;
	erromes = scanf("%zu", &price);
	CleanBuffer();
	printf("添加成功\n");
	if (NumInputFailure(erromes)) {
		printf("输入错误。\n");
		return;
	}
	Commodity* commodity = NewProduct(name, price);	//构造对象
	if (!commodity) {
		return;
	}
	PushFront(g_Commodity, commodity);	//插入对象
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
	return Find(g_Commodity, FindName, name);
}

// 修改商品
void ModifyProducts()
{
	Node* node = ChooseProduct();
	if (!node) {
		printf("未有此商品。\n");
		return;
	}
	system("cls");
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
		strncpy(((Commodity*)(node->m_Data))->m_CommodityName, name, sizeof(name));
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



// 打印订单链表
void PrintOrderForm(void* pValue, void* operateValue)
{
	OrderForm* orderForm = (OrderForm*)(pValue);
	printf("%zu\t%s\t%zu\t%zu\t%s\t%s\t%s\t%s\n",
		orderForm->m_OrderNumber, orderForm->m_CommodityName,
		orderForm->m_CommodityNum, orderForm->m_CommodityPrices,
		orderForm->m_UserName, orderForm->m_UserPhoneNum,
		orderForm->m_UserAddress, orderForm->m_OrderStatus);
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
	printf("请选择要修改的成员:\n");
	printf("0.取消修改\t\t1.配送中\t\t2.已送达\n");
	scanf("%d", &select);
	CleanBuffer();
	system("cls");
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




void SaveOrderForm(void* pValue, void* operateValue)
{
	FILE* pfw = (FILE*)operateValue;
	fwrite(pValue, sizeof(OrderForm), 1, pfw);
}

void SaveCommodity(void* pValue, void* operateValue)
{
	FILE* pfw = (FILE*)operateValue;
	fwrite(pValue, sizeof(Commodity), 1, pfw);
}



void MerchantUI()
{
	if (!MerchantLogin()) {	//登录失败则退出
		return;
	}
	enum MerchantMenu {
		EXIT,
		ADDPRODUCTS,
		VIEWPRODUCTS,
		MODIFYPRODUCTS,
		MANAGEDISTRIBUTE
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
			FILE* opfw = fopen("OrderForm.dat", "wb");	//创建文件
			if (opfw == NULL) {
				printf("%s", strerror(errno));
				return;
			}
			TraversalOperation(g_OrderForm, SaveOrderForm, opfw);
			FILE* cpfw = fopen("Commodity.dat", "wb");	//创建文件
			if (cpfw == NULL) {
				printf("%s", strerror(errno));
				return;
			}
			TraversalOperation(g_Commodity, SaveCommodity, cpfw);
			fclose(opfw);
			fclose(cpfw);
			break;
		}
		case ADDPRODUCTS: {	// 添加商品
			AddProducts();
			getchar();
			break;
		}
		case VIEWPRODUCTS: {	//查看商品
			TraversalOperation(g_Commodity, PrintProducts, NULL);
			getchar();
			break;
		}
		case MODIFYPRODUCTS: {
			ModifyProducts();
			getchar();
			break;
		}
		case MANAGEDISTRIBUTE: {
			ManageDistribute();
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

