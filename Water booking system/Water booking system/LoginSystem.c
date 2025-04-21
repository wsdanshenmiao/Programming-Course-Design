#define _CRT_SECURE_NO_WARNINGS

#include "LoginSystem.h"
#include "windows.h"

#define MALLOC(T) ((T*)malloc(sizeof(T)))


//用户登录
Node* UserLogin()
{
	Userinfo e; //用户信息结构体
	int erromes;
	Node* node = NULL;

	printf("请输入登录的用户名：\n");
	erromes = scanf("%s", e.m_Username);
	CleanBuffer();
	if (StrInputFailure(erromes, e.m_Username, sizeof(e.m_Username))) {
		printf("用户名输入错误。\n");
		return NULL;
	}

	node = Find(g_Userinfo, FindUser, e.m_Username);
	if (node == NULL) {
		printf("用户名不存在\n");
		return NULL;
	}

	printf("请输入登录的密码：\n");
	erromes = scanf("%s", e.m_Password);
	CleanBuffer();
	if (StrInputFailure(erromes, e.m_Password, sizeof(e.m_Password))) {
		printf("密码输入错误。\n");
		return NULL;
	}

	if (strncmp(((Userinfo*)(node->m_Data))->m_Password, e.m_Password, sizeof(e.m_Password)) != 0) {
		printf("密码不匹配\n");
		return NULL;
	}

	return node;
}




// 显示账号信息,这里没有显示账号的密码
void PrintUser(void* pValue)
{
	Userinfo* userinfo = (Userinfo*)pValue;
	printf("%s\t%s\t%s\t%lld\n", userinfo->m_Username, userinfo->m_UserPhoneNum, userinfo->m_Address,
		userinfo->m_Balance);
}

//构造对象
Userinfo* NewUser(Userinfo e)
{
	Userinfo* userinfo = MALLOC(Userinfo);
	if (!userinfo) {
		return NULL;
	}
	strncpy(userinfo->m_Username, e.m_Username, sizeof(e.m_Username));
	strncpy(userinfo->m_Password, e.m_Password, sizeof(e.m_Password));
	strncpy(userinfo->m_UserPhoneNum, e.m_UserPhoneNum, sizeof(e.m_UserPhoneNum));
	strncpy(userinfo->m_Address, e.m_Address, sizeof(e.m_Address));
	userinfo->m_Balance = e.m_Balance;
	return userinfo;
}

//用户注册
void UserRegister()
{
	Userinfo e; //用户信息结构体
	int erromes;

	printf("请输入注册的用户名：\n");
	erromes = scanf("%s", e.m_Username);
	CleanBuffer();
	if (StrInputFailure(erromes, e.m_Username, sizeof(e.m_Username))) {
		printf("输入错误。\n");
		return;
	}

	if (Find(g_Userinfo, FindUser, e.m_Username)) {
		printf("用户名已经存在\n");
		return;
	}

	printf("请输入注册的密码：\n");
	erromes = scanf("%s", e.m_Password);
	CleanBuffer();
	if (StrInputFailure(erromes, e.m_Password, sizeof(e.m_Password))) {
		printf("输入错误。\n");
		return;
	}

	printf("请输入注册的用户手机号：\n");
	erromes = scanf("%s", e.m_UserPhoneNum);
	CleanBuffer();
	if (StrInputFailure(erromes, e.m_UserPhoneNum, sizeof(e.m_UserPhoneNum))) {
		printf("输入错误。\n");
		return;
	}

	printf("请输入注册的用户地址：\n");
	erromes = scanf("%s", e.m_Address);
	CleanBuffer();
	if (StrInputFailure(erromes, e.m_Address, sizeof(e.m_Address))) {
		printf("输入错误。\n");
		return;
	}

	printf("请输入注册的用户余额：\n");
	erromes = scanf("%lld", &e.m_Balance);
	CleanBuffer();
	if (NumInputFailure(erromes)) {
		printf("输入错误。\n");
		return;
	}

	Userinfo* userinfo = NewUser(e);	//构造对象
	if (!userinfo) {
		return;
	}
	PushFront(g_Userinfo, userinfo);	//插入对象
}

// 账号查找函数,防止重复账号
bool FindUser(void* pValue, void* cmpValue)
{
	Userinfo* userinfo = (Userinfo*)pValue;
	return strncmp(userinfo->m_Username, (char*)cmpValue, sizeof((char*)cmpValue)) == 0;
}


//保存账号信息
void SaveUserinfo(void* pValue, void* operateValue)
{
	FILE* pfw = (FILE*)operateValue;
	fwrite(pValue, sizeof(Userinfo), 1, pfw);
}

void UserLoginCatalogue()
{
	printf("**************   0.返回主界面     ********************\n");
	printf("**************   1.用户注册       ********************\n");
	printf("**************   2.用户登录       ********************\n");
}

Node* UserLoginUI()
{
	enum UserMenu {
		EXIT, USERREGISTER, USERLOGIN
	};
	enum UserMenu select;
	do {
		UserLoginCatalogue();	//打印目录
		printf("请选择:");
		scanf("%d", &select);
		CleanBuffer();
		system("cls");
		switch (select) {
		case EXIT: {	//保存用户信息并退出
			FILE* pfw = fopen("Userinfo.dat", "wb");	//创建文件
			if (pfw == NULL) {
				printf("%s", strerror(errno));
				return;
			}
			TraversalOperation(g_Userinfo, SaveUserinfo, pfw);
			fclose(pfw);
			break;
		}
		case USERREGISTER: {  //用户注册
			UserRegister();
			getchar();
			break;
		}
		case USERLOGIN: {//用户登录

			Node* node = UserLogin();
			if (!node) {
				printf("登录失败\n");
			}
			else {
				printf("登录成功\n");
				Sleep(1000);
				return node;
			}
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


//商家登录
bool MerchantLogin()
{
	FILE* pfr;
	if (_access("Merchant.dat", 0)) {
		pfr = fopen("Merchant.dat", "wb");
	}
	else {
		pfr = fopen("Merchant.dat", "rb");
	}
	char correctPassword[20];
	fread(correctPassword, sizeof(correctPassword), 1, pfr);

	printf("请输入密码：\n");
	char password[20];
	int erromes = scanf("%s", password);
	CleanBuffer();
	if (StrInputFailure(erromes, password, sizeof(password))) {
		printf("输入错误。\n");
		return false;
	}
	if (strncmp(correctPassword, password, sizeof(password)) == 0) {
		printf("登录成功。\n");
		Sleep(1000);
		return true;
	}
	else {
		printf("登录失败。\n");
		Sleep(1000);
		return false;
	}
}

