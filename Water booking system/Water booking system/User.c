#define _CRT_SECURE_NO_WARNINGS

#include"User.h"
#include"windows.h"

#define MALLOC(T) ((T*)malloc(sizeof(T)))
#define ASSERTPOINTER(T) if (!(T)) {return NULL;}



// 用户充值
bool RechargeUserAccount(Userinfo* user, size_t amount) {
	if (user == NULL || amount == 0) {
		return false; // 如果用户不存在或充值金额为0，则返回失败
	}
	user->m_Balance += amount; // 更新用户余额
	return true;
}

// 用户充值
void Recharge(Node* userMes)
{
	// 用户信息在登录时就找到了，不用再输了    
	Userinfo* userinfo = (Userinfo*)(userMes->m_Data);
	size_t amount;
	printf("当前余额：%zu\n", userinfo->m_Balance);
	printf("请输入充值金额：\n");
	int error = scanf("%zu", &amount); // 获取用户输入的充值金额
	CleanBuffer();
	if (NumInputFailure(error)) { // 检查输入是否失败
		printf("输入错误，请重新输入。\n");
		return;
	}


	userinfo->m_Balance += amount;   // 这里没必要写成函数
	printf("充值成功，当前余额：%zu\n", userinfo->m_Balance); // 充值成功，打印当前余额
	Sleep(1000);
}




void PrintCommofity(void* pValue, void* operateValue)
{
	Commodity* commofity = (Commodity*)(pValue);
	printf("%s\t%lld\n",
		commofity->m_CommodityName,
		commofity->m_CommodityPrices);
}

bool FindProduct(void* pValue, void* cmpValue)
{
	Commodity* commodity = (Commodity*)pValue;
	return strncmp(commodity->m_CommodityName, (char*)cmpValue, sizeof((char*)cmpValue)) == 0;
}

// 用户选择商品
Node* SelectProduct() {
	printf("请输入商品名称：\n"); // 提示用户输入商品名称
	char name[20]; // 存储输入的商品名称
	int error = scanf("%s", name); // 读取用户输入
	CleanBuffer(); // 清除输入缓冲区
	if (StrInputFailure(error, name, sizeof(name))) { // 检查输入是否失败
		printf("输入错误，请重新输入。\n");
		return NULL; // 输入失败时返回 NULL
	}
	Node* node = Find(g_Commodity, FindProduct, name); // 在商品链表中查找商品
	if (!node) {
		printf("未找到该商品。\n"); // 若未找到商品，输出提示
	}
	return node; // 返回找到的商品节点
}

// 用户输入购买数量
size_t GetUserQuantity() {
	printf("请输入购买数量：\n"); // 提示用户输入购买数量
	size_t quantity; // 存储购买数量
	int error = scanf("%zu", &quantity); // 读取用户输入的数量
	CleanBuffer(); // 清除输入缓冲区
	if (NumInputFailure(error) || quantity <= 0) { // 检查输入是否失败
		printf("请输入大于0的数字。\n");
		return 0; // 输入失败返回0
	}
	return quantity; // 返回输入的数量
}

// 创建订单
OrderForm* CreateOrder(Commodity* commodity, Userinfo* userinfo, size_t quantity)
{
	OrderForm* order = MALLOC(OrderForm); // 分配内存给订单
	ASSERTPOINTER(order);
	order->m_OrderNumber = rand();  // 随机生成订单号
	order->m_CommodityNum = quantity; // 设置购买数量
	order->m_CommodityPrices = commodity->m_CommodityPrices * quantity; // 计算总价格
	strncpy(order->m_UserName, userinfo->m_Username, sizeof(order->m_UserName)); // 设置用户名
	strncpy(order->m_UserPhoneNum, userinfo->m_UserPhoneNum, sizeof(order->m_UserPhoneNum)); // 设置用户电话号码
	strncpy(order->m_CommodityName, commodity->m_CommodityName, sizeof(order->m_CommodityName)); // 设置商品名称
	strncpy(order->m_UserAddress, userinfo->m_Address, sizeof(order->m_UserAddress)); // 设置用户地址
	strncpy(order->m_OrderStatus, "待发货", sizeof("待发货")); // 设置订单状态为“待发货”
	return order; // 返回创建的订单
}

// 用户购买商品
void PurchaseProduct(Node* userMes)
{
	TraversalOperation(g_Commodity, PrintCommofity, NULL);
	Node* selectedProduct = SelectProduct(); // 用户选择商品
	if (!selectedProduct) {
		return; // 如果商品选择失败，返回
	}
	size_t quantity = GetUserQuantity(); // 获取用户输入的购买数量
	if (quantity == 0) {
		return; // 如果输入的数量为0，返回
	}
	Commodity* commodity = (Commodity*)(selectedProduct->m_Data);
	Userinfo* userinfo = (Userinfo*)(userMes->m_Data);  //用户信息在登录时就可以找到
	OrderForm* order = CreateOrder(commodity, userinfo, quantity); // 创建订单
	if (!order) {
		printf("订单创建失败。\n"); // 如果订单创建失败，输出提示
		return;
	}
	PushFront(g_OrderForm, order); // 将订单加入订单链表          这就没必要写成函数了
	printf("订单提交成功！订单号：%zu\n", order->m_OrderNumber); // 输出订单提交成功信息及订单号
}




bool IsNumber(const char* str, size_t num)
{
	for (int i = 0; i < num; ++i) {
		if (!isalnum(str[i])) {
			return false;
		}
	}
	return true;
}

void InformChange(Node* userMes)
{
	enum Modify {
		EXIT, NAME, PASSWORD, PHONENUMBER, ADDRESS
	};
	enum Modify select;
	Userinfo* userinfo = (Userinfo*)(userMes->m_Data);
	printf("请选择要修改的信息:\n");
	printf("0.取消修改\t\t1.名字\t\t2.密码\t\t3.手机号\t\t4.地址\n");
	scanf("%d", &select);
	CleanBuffer();
	system("cls");
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
		strncpy(userinfo->m_Username, name, sizeof(name));
		printf("修改成功。\n");
		break;
	}
	case PASSWORD: {
		printf("请输入新的密码：\n");
		char password1[20];
		int erromes = scanf("%s", password1);
		CleanBuffer();
		if (StrInputFailure(erromes, password1, sizeof(password1)) || !IsNumber(password1, sizeof(password1))) {
			printf("输入错误。\n");
			return;
		}
		printf("请确认新的密码：\n");
		char password2[20];
		erromes = scanf("%s", password2);
		CleanBuffer();
		if (StrInputFailure(erromes, password2, sizeof(password2)) || !IsNumber(password2, sizeof(password2))) {
			printf("输入错误。\n");
			return;
		}
		if (strncmp(password1, password2, sizeof(password1) == 0)) {
			strncpy(userinfo->m_Password, password2, sizeof(password2));
			printf("修改成功。\n");
		}
		else {
			printf("输入不相同。\n");
			return;
		}
		break;
	}
	case PHONENUMBER: {
		printf("请输入新的手机号：\n");
		char phoneNum[20];
		int erromes = scanf("%s", phoneNum);
		CleanBuffer();
		if (StrInputFailure(erromes, phoneNum, sizeof(phoneNum)) || !IsNumber(phoneNum, sizeof(phoneNum))) {
			printf("输入错误。\n");
			return;
		}
		strncpy(userinfo->m_UserPhoneNum, phoneNum, sizeof(phoneNum));
		printf("修改成功。\n");
		break;
	}
	case ADDRESS: {
		printf("请输入新的名字：\n");
		char address[40];
		int erromes = scanf("%s", address);
		CleanBuffer();
		if (StrInputFailure(erromes, address, sizeof(address))) {
			printf("输入错误。\n");
			return;
		}
		strncpy(userinfo->m_Address, address, sizeof(address));
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



void UserCatalogue()
{
	printf("*****************  0.返回主界面      ********************\n");
	printf("*****************  1.购买商品        ********************\n");
	printf("*****************  2.账户充值        ********************\n");
	printf("*****************  3.资料修改        ********************\n");
}


void UserUI()
{

	Node* UserMes = UserLoginUI();
	if (!UserMes) {
		return;
	}

	enum UserMenu {
		EXIT, PURCHASEPRODUCT, RECHARGE, INFORMCHANGE
	};
	enum MasterMenu select;
	do {
		system("cls");
		UserCatalogue();	//打印目录
		printf("请选择:");
		scanf("%d", &select);
		CleanBuffer();
		system("cls");
		switch (select) {
		case EXIT: {
			FILE* pfw = fopen("Userinfo.dat", "wb");	//创建文件
			if (pfw == NULL) {
				printf("%s", strerror(errno));
				return;
			}
			TraversalOperation(g_Userinfo, SaveUserinfo, pfw);
			fclose(pfw);
			break;
		}
		case PURCHASEPRODUCT: {
			PurchaseProduct(UserMes);
			break;
		}
		case RECHARGE: {
			Recharge(UserMes);
			break;
		}
		case INFORMCHANGE: {
			InformChange(UserMes);
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

