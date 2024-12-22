#include "LoginSystem.h"
#include "ManagementAPP.h"
#include "Client.h"
#include "Administrator.h"



ListNode* ManagementAPPLogin(
	char* fileName,
	DoubleList* infoList,
	void registe(DoubleList*),
	ListNode* findInfo(DoubleList*),
	void saveInfo(void*, void*),
	char* catalogue)
{
	assert(ASSERTPOINTER(infoList) && ASSERTPOINTER(catalogue));

	enum LoginMenu {
		EXIT = 0, REGISTER = 1, LOGIN = 2
	};
	enum LoginMenu select;

	do {
		printf("%s", catalogue);
		printf("请选择:");
		scanf("%d", &select);
		CleanInputBuffer();
		system("cls");
		switch (select) {
		case EXIT: {	//保存信息并退出
			break;
		}
		case REGISTER: {  //注册
			registe(infoList);
			SaveInfoToFile(fileName, infoList, saveInfo);
			break;
		}
		case LOGIN: {	//登录
			ListNode* node = findInfo(infoList);
			if (NULL == node) {
				printf("登录失败\n");
			}
			else {
				printf("登录成功\n");
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

	return NULL;
}

ListNode* ClientLogin(ManagementAPP* app)
{
	assert(ASSERTPOINTER(app));
	char* catalogue =
		"**************   0.返回主界面     ********************\n"
		"**************   1.用户注册       ********************\n"
		"**************   2.用户登录       ********************\n";
	return ManagementAPPLogin(
		app->m_ClientDataFileName,
		app->m_ClientData,
		ClientRegiste,
		FindClientInfo,
		SaveClientInfo,
		catalogue);
}

void ClientRegiste(DoubleList* infoList)
{
	assert(ASSERTPOINTER(infoList));

	ClientInfo client; //用户信息结构体
	int erromes = 0;
	ListNode* node = NULL;

	printf("请输入注册的用户名：\n");
	erromes = scanf("%s", client.m_ClientName);
	CleanInputBuffer();
	if (StrInputFailure(erromes, client.m_ClientName, sizeof(client.m_ClientName))) {
		printf("输入错误。\n");
		return;
	}

	node = ListFindNode(infoList, client.m_ClientName, CmpClientDataByName);
	if (ListEnd(infoList) != node) {
		printf("用户名已经存在\n");
		return;
	}

	printf("请输入注册的密码：\n");
	erromes = scanf("%s", client.m_Password);
	CleanInputBuffer();
	if (StrInputFailure(erromes, client.m_Password, sizeof(client.m_Password))) {
		printf("输入错误。\n");
		return;
	}

	printf("请输入注册的用户手机号：\n");
	erromes = scanf("%s", client.m_ClientPhoneNum);
	CleanInputBuffer();
	if (StrInputFailure(erromes, client.m_ClientPhoneNum, sizeof(client.m_ClientPhoneNum))) {
		printf("输入错误。\n");
		return;
	}

	printf("请输入注册的用户余额：\n");
	erromes = scanf("%lld", &client.m_Balance);
	CleanInputBuffer();
	if (NumInputFailure(erromes)) {
		printf("输入错误。\n");
		return;
	}

	node = ListPushBack(infoList);	//插入对象
	if (NULL != node) {
		memcpy(node->m_Data, &client, sizeof(ClientInfo));
	}
}

ListNode* AdministratorLogin(ManagementAPP* app)
{
	assert(ASSERTPOINTER(app));
	char* catalogue =
		"**************   0.返回主界面     ********************\n"
		"**************   1.管理员注册     ********************\n"
		"**************   2.管理员登录     ********************\n";
	return ManagementAPPLogin(
		app->m_AdministratorDataFileName,
		app->m_AdministratorData,
		AdministratorRegiste,
		FindAdministratorInfo,
		SaveAdministratorInfo,
		catalogue);
}

void AdministratorRegiste(DoubleList* infoList)
{
	assert(ASSERTPOINTER(infoList));

	size_t id = 0;
	char password[20] = "";
	int erromes = 0;
	ListNode* node = NULL;

	printf("请输入注册的ID：\n");
	erromes = scanf("%lld", &id);
	CleanInputBuffer();
	if (NumInputFailure(erromes)) {
		printf("输入错误。\n");
		return;
	}

	node = ListFindNode(infoList, &id, CmpAdministratorDataByID);
	if (ListEnd(infoList) != node) {
		printf("用户名已经存在\n");
		return;
	}

	printf("请输入注册的密码：\n");
	erromes = scanf("%s", password);
	CleanInputBuffer();
	if (StrInputFailure(erromes, password, sizeof(password))) {
		printf("输入错误。\n");
		return;
	}

	node = ListPushBack(infoList);	//插入对象
	AdministratorInfo* admini = (AdministratorInfo*)node->m_Data;
	admini->m_ID = id;
	strncpy(admini->m_Password, password, sizeof(password));
}

