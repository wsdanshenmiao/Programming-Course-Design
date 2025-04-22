#define _CRT_SECURE_NO_WARNINGS

#include "Util.h"

void CleanBuffer()
{
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}

// 字符串输入检测，输入失败返回true/1
bool StrInputFailure(int erromes, char* name, size_t size)
{
	if (!name) {
		return true;
	}
	size_t len = strnlen(name, size);
	if (!erromes || erromes == EOF || len == 0 || len >= size) {
		return true;
	}
	return false;
}

// 数字输入检测，输入失败返回true/1
bool NumInputFailure(int erromes)
{
	if (!erromes || erromes == EOF) {
		return true;
	}
	return false;
}



void SaveUserinfoFunc(void* pValue, void* operateValue)
{
	FILE* pfw = (FILE*)operateValue;
	fwrite(pValue, sizeof(Userinfo), 1, pfw);
}
//保存账号信息
void SaveUserinfo()
{
	FILE* pfw = fopen("Userinfo.dat", "wb");	//创建文件
	if (pfw == NULL) {
		printf("%s", strerror(errno));
		return;
	}
	TraversalOperation(g_Userinfo, SaveUserinfoFunc, pfw);
	fclose(pfw);
}

// 保存订单
void SaveOrderFormFunc(void* pValue, void* operateValue)
{
	FILE* pfw = (FILE*)operateValue;
	fwrite(pValue, sizeof(OrderForm), 1, pfw);
}
void SaveOrderForm()
{
	FILE* opfw = fopen("OrderForm.dat", "wb");	//创建文件
	if (opfw == NULL) {
		printf("%s", strerror(errno));
		return;
	}
	TraversalOperation(g_OrderForm, SaveOrderFormFunc, opfw);
	fclose(opfw);
}

// 保存商品信息
void SaveCommodityFunc(void* pValue, void* operateValue)
{
	FILE* pfw = (FILE*)operateValue;
	fwrite(pValue, sizeof(Commodity), 1, pfw);
}
void SaveCommodity()
{
	FILE* cpfw = fopen("Commodity.dat", "wb");	//创建文件
	if (cpfw == NULL) {
		printf("%s", strerror(errno));
		return;
	}
	TraversalOperation(g_Commodity, SaveCommodityFunc, cpfw);
	fclose(cpfw);
}


// 打印订单链表
void PrintOrderForm(void* pValue, void* operateValue)
{
	OrderForm* orderForm = (OrderForm*)(pValue);
	printf("订单编号：%zu\t商品名称：%s\t购买数量：%zu\t订单总价：%zu\t未送数量：%zu\t已送数量：%zu\t买方用户名：%s\n买方电话：%s\t买方地址：%s\t订单状态：%s\n",
		orderForm->m_OrderNumber, orderForm->m_CommodityName,
		orderForm->m_CommodityNum, orderForm->m_CommodityPrices,
		orderForm->m_UndeliverNum, orderForm->m_DeliverNum,
		orderForm->m_UserName, orderForm->m_UserPhoneNum,
		orderForm->m_UserAddress, orderForm->m_OrderStatus);
	printf("\n-----------------------------------------------------------------------------------------------\n");
}

// 打印商品
void PrintCommofity(void* pValue, void* operateValue)
{
	Commodity* commofity = (Commodity*)(pValue);
	printf("名称：%s\t单价：%zu\n",
		commofity->m_CommodityName,
		commofity->m_CommodityPrices);
}

// 打印全部账号信息
void PrintUserAll(void* pValue, void* operateValue)
{
	Userinfo* userinfo = (Userinfo*)pValue;
	printf("用户名：%s\t 密码：%s\t 电话：%s\t 地址：%s\t 余额：%zu\n",
		userinfo->m_Username,
		userinfo->m_Password,
		userinfo->m_UserPhoneNum,
		userinfo->m_Address,
		userinfo->m_Balance);
}

// 打印账号信息,这里没有显示账号的密码
void PrintUser(void* pValue, void* operateValue)
{
	Userinfo* userinfo = (Userinfo*)pValue;
	printf("%s\t%s\t%s\t%lld\n",
		userinfo->m_Username,
		userinfo->m_UserPhoneNum,
		userinfo->m_Address,
		userinfo->m_Balance);
}


bool IsNumber(const char* str, size_t num)
{
	if (!str) {
		return false;
	}
	for (int i = 0; i < num; ++i) {
		if ('0' > str[i] || str[i] > '9') {
			return false;
		}
	}
	return true;
}

bool IsAllAlphaNumeric(const char* str, size_t num)
{
	// 检查指针是否为空
	if (str == NULL) {
		return false;
	}
	// 遍历字符串直到遇到空字符 '\0'
	for (size_t i = 0; str[i] != '\0' && i < num; ++i) {
		// 如果当前字符不是字母或数字字符，返回 false
		if (!('0' <= str[i] && str[i] <= '9') &&
			!('a' <= str[i] && str[i] <= 'z') &&
			!('z' <= str[i] && str[i] <= 'Z')) {
			return false;
		}
	}
	// 如果所有字符都是字母或数字字符，返回 true
	return true;
}