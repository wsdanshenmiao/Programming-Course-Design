#define _CRT_SECURE_NO_WARNINGS

#include"User.h"
#include"windows.h"

#define MALLOC(T) ((T*)malloc(sizeof(T)))
#define ASSERTPOINTER(T) if (!(T)) {return NULL;}



//电话查找函数，防止重复电话
bool FindPhoneNum(void* pValue, void* cmpValue)
{
    Userinfo* userinfo = (Userinfo*)pValue;
    return strncmp(userinfo->m_UserPhoneNum, (char*)cmpValue, sizeof((char*)cmpValue)) == 0;
}

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
    int amount;
    printf("当前余额：%zu\n", userinfo->m_Balance);
    printf("请输入充值金额：\n");
    int error = scanf("%d", &amount); // 获取用户输入的充值金额
    CleanBuffer();
    if (amount < 0) {
        printf("输入错误，请重新输入。\n");
        Sleep(1000);
        return;
    }
    if (NumInputFailure(error)) { // 检查输入是否失败
        printf("输入错误，请重新输入。\n");
        Sleep(1000);
        return;
    }

    userinfo->m_Balance += amount;   // 这里没必要写成函数
    printf("充值成功，当前余额：%zu\n", userinfo->m_Balance); // 充值成功，打印当前余额
    Sleep(1000);
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
        Sleep(1000);
        return NULL; // 输入失败时返回 NULL
    }
    Node* node = Find(g_Commodity, FindProduct, name); // 在商品链表中查找商品
    if (!node) {
        printf("未找到该商品。\n"); // 若未找到商品，输出提示
        Sleep(1000);
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
OrderForm* CreateOrder(Commodity* commodity, Userinfo* userinfo, size_t quantity, char orderType[10])
{
    OrderForm* order = MALLOC(OrderForm); // 分配内存给订单
    ASSERTPOINTER(order);
    srand(time(0));
    // 即定即取配送全部，批量定取全部存库存里，用户自行选择是否配送
    size_t deliverNum = strncmp(orderType, "即定即取", sizeof("即定即取")) ? 0 : quantity;
    order->m_OrderNumber = rand();  // 随机生成订单号
    order->m_CommodityNum = quantity; // 设置购买数量
    order->m_DeliverNum = deliverNum;    // 已配送
    order->m_UndeliverNum = quantity - deliverNum;  //库存
    order->m_CommodityPrices = commodity->m_CommodityPrices * quantity; // 计算总价格
    strncpy(order->m_UserName, userinfo->m_Username, sizeof(order->m_UserName)); // 设置用户名
    strncpy(order->m_UserPhoneNum, userinfo->m_UserPhoneNum, sizeof(order->m_UserPhoneNum)); // 设置用户电话号码
    strncpy(order->m_CommodityName, commodity->m_CommodityName, sizeof(order->m_CommodityName)); // 设置商品名称
    strncpy(order->m_UserAddress, userinfo->m_Address, sizeof(order->m_UserAddress)); // 设置用户地址
    strncpy(order->m_OrderStatus, "待发货", sizeof("待发货")); // 设置订单状态为“待发货”
    strncpy(order->m_OrderType, orderType, sizeof(order->m_OrderType));
    return order; // 返回创建的订单
}

char* ChoseOrderType()
{
    printf("0.取消订购\t1.即定即取\t2.批量定取\n");
    printf("请选择订单种类：\n");
    int select;
    scanf("%d", &select);
    CleanBuffer();
    switch (select) {
    case 0: {
        return NULL;
        break;
    }
    case 1: { 
        return "即定即取";
        break;
    }
    case 2: { 
        return "批量定取";
        break;
    }
    default: {
        printf("输入错误。\n");
        getchar();
        break;
    }
    }
    return NULL;
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
    size_t totalPrice = commodity->m_CommodityPrices * quantity;
    if (userinfo->m_Balance >= totalPrice) {
        userinfo->m_Balance = userinfo->m_Balance - totalPrice;
    }
    else{
        printf("余额不足，购买失败");
        Sleep(1000);
        return;
    }

    char* orderType = ChoseOrderType();
    if (!orderType) {
        return;
    }

    OrderForm* order = CreateOrder(commodity, userinfo, quantity, orderType); // 创建订单
    if (!order) {
        printf("订单创建失败。\n"); // 如果订单创建失败，输出提示
        Sleep(1000);
        return;
    }
    PushFront(g_OrderForm, order); // 将订单加入订单链表          这就没必要写成函数了
    printf("订单提交成功！订单号：%zu\n", order->m_OrderNumber); // 输出订单提交成功信息及订单号
    Sleep(1000);
}




bool CompareArrays(const char* arr1, const char* arr2) {
    // 检查两个数组的每个字符是否相等，直到遇到空字符 '\0'
    while (*arr1 != '\0' && *arr2 != '\0') {
        if (*arr1 != *arr2) {
            return false;
        }
        ++arr1;
        ++arr2;
    }
    // 如果两个数组都遍历到了末尾（空字符 '\0'），则认为相等；否则认为不相等
    return (*arr1 == '\0' && *arr2 == '\0');
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
    //system("cls");
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
            Sleep(1000);
            return;
        }

        if (Find(g_Userinfo, FindUser, name)) {
            printf("用户名已经存在\n");
            Sleep(1000);
            return;
        }

        strncpy(userinfo->m_Username, name, sizeof(name));
        printf("修改成功。\n");
        Sleep(1000);
        break;
    }
    case PASSWORD: {
        printf("请输入新的密码：\n");
        char password1[20];
        int erromes = scanf("%s", password1);
        CleanBuffer();
        if (StrInputFailure(erromes, password1, sizeof(password1)) || !IsAllAlphaNumeric(password1, sizeof(password1))) {
            printf("请输入符合格式要求的密码1。\n");
            Sleep(1000);
            return;
        }
        printf("请确认新的密码：\n");
        char password2[20];
        erromes = scanf("%s", password2);
        CleanBuffer();
        if (StrInputFailure(erromes, password2, sizeof(password2)) || !IsAllAlphaNumeric(password2, sizeof(password1))) {
            printf("请输入符合格式要求的密码2。\n");
            Sleep(1000);
            return;
        }
        if (strncmp(password1, password2, sizeof(password1)) == 0) {
            strncpy(userinfo->m_Password, password2, sizeof(password2));
            printf("修改成功。\n");
            Sleep(1000);
        }
        else {
            printf("输入不相同。\n");
            Sleep(1000);
            return;
        }
        break;
    }
    case PHONENUMBER: {
        printf("请输入新的手机号：\n");
        char phoneNum[20];
        int erromes = scanf("%s", phoneNum);
        CleanBuffer();
        
        if (StrInputFailure(erromes, phoneNum, sizeof(phoneNum)) || IsNumber(phoneNum, sizeof(phoneNum))) {
            printf("请输入符合格式要求的电话号码。\n");
            Sleep(1000);
            return;
        }
        if (strlen(phoneNum) != 11) {
            printf("请输入符合长度要求的电话号码。\n");
            Sleep(1000);
            return;
        }
        if (Find(g_Userinfo, FindPhoneNum, phoneNum)) {
            printf("该电话已被注册\n");
            Sleep(1000);
            return;
        }
        strncpy(userinfo->m_UserPhoneNum, phoneNum, sizeof(phoneNum));
        printf("修改成功。\n");
        Sleep(1000);
        break;
    }
    case ADDRESS: {
        printf("请输入新的地址：\n");
        char address[40];
        int erromes = scanf("%s", address);
        CleanBuffer();
        if (StrInputFailure(erromes, address, sizeof(address))) {
            printf("输入错误。\n");
            Sleep(1000);
            return;
        }
        strncpy(userinfo->m_Address, address, sizeof(address));
        printf("修改成功。\n");
        Sleep(1000);
        break;
    }
    default: {
        printf("输入错误。\n");
        Sleep(1000);
        getchar();
        break;
    }
    }
}


void TraversalStock(void* pValue, void* operateValue)
{
    Userinfo* userinfo = (Userinfo*)operateValue;
    OrderForm* order = (OrderForm*)pValue;
    if (!strncmp(order->m_UserName, userinfo->m_Username, sizeof(userinfo->m_Username)) &&
        !strncmp(order->m_OrderType, "批量定取", sizeof("批量定取"))) {
        printf("商品名：%s\t商品编号：%zu\t已提取数量：%zu\t未提取数量：%zu\n", 
            order->m_CommodityName,
            order->m_OrderNumber,
            order->m_DeliverNum,
            order->m_UndeliverNum);
    }
}

bool FindStock(void* pValue, void* cmpValue)
{
    OrderForm* order = (OrderForm*)pValue;
    size_t orderNum = *((size_t*)cmpValue);
    return order->m_OrderNumber == orderNum;
}

void DrawStock(Node* userMes)
{
    Userinfo* userinfo = (Userinfo*)(userMes->m_Data);
    TraversalOperation(g_OrderForm, TraversalStock, userinfo);
    printf("请选择要提取订单,或输入0退出。\n");
    size_t orderNum;
    int error = scanf("%zu", &orderNum);
    CleanBuffer();
    if (NumInputFailure(error) || orderNum == 0) {
        return;
    }
    Node* node = Find(g_OrderForm, FindStock, &orderNum);
    if (!node) {
        printf("无此订单。\n");
        getchar();
        return;
    }
    printf("请输入要提取的数量。\n");
    size_t num;
    error = scanf("%zu", &num);
    CleanBuffer();
    if (NumInputFailure(error)) {
        printf("输入错误。\n");
        getchar();
        return;
    }
    OrderForm* order = (OrderForm*)(node->m_Data);
    if (num < 0 || num > order->m_UndeliverNum) {
        printf("输入错误。\n");
        getchar();
        return;
    }
    order->m_UndeliverNum -= num;
    order->m_DeliverNum += num;
    if (order->m_UndeliverNum == 0) {
        strncpy(order->m_OrderStatus, "已配送", sizeof("已配送"));
    }
    printf("提取成功。\n");
}


void UserCatalogue()
{
    printf("*****************  0.返回主界面      ********************\n");
    printf("*****************  1.购买商品        ********************\n");
    printf("*****************  2.账户充值        ********************\n");
    printf("*****************  3.资料修改        ********************\n");
    printf("*****************  4.查看资料        ********************\n");
    printf("*****************  5.查看库存并提取  ********************\n");
}


void UserUI()
{

    Node* UserMes = UserLoginUI();
    if (!UserMes) {
        return;
    }
    enum UserMenu {
        EXIT, PURCHASEPRODUCT, RECHARGE, INFORMCHANGE, CHECKMATERIAL, DRAWSTOCK
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
            SaveUserinfo();
            SaveOrderForm();
            break;
        }
        case PURCHASEPRODUCT: { //购买商品
            PurchaseProduct(UserMes);
            SaveOrderForm();
            break;
        }
        case RECHARGE: {    //充值
            Recharge(UserMes);
            SaveUserinfo();
            break;
        }
        case INFORMCHANGE: {    //修改个人信息
            PrintUserAll(UserMes->m_Data, NULL);
            InformChange(UserMes);
            SaveUserinfo();
            break;
        }
        case CHECKMATERIAL: {   // 查看个人信息
            PrintUserAll(UserMes->m_Data, NULL);
            getchar();
            break;
        }
        case DRAWSTOCK: {   // 查看库存并提取
            DrawStock(UserMes);
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

