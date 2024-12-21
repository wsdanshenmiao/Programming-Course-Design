#include "Client.h"
#include "ManagementAPP.h"
#include "LoginSystem.h"

void* CreateClientData()
{
	ClientInfo* clientData = MALLOC(ClientInfo);
	if (NULL == clientData)return NULL;

	return (void*)clientData;
}

int CmpClientDataByBalance(void* c0, void* c1)
{
	assert(ASSERTPOINTER(c0) && ASSERTPOINTER(c1));
	size_t balance0 = ((ClientInfo*)c0)->m_Balance;
	size_t balance1 = ((ClientInfo*)c1)->m_Balance;
	if (balance0 > balance1)return 1;
	else if (balance0 == balance1)return 0;
	else return-1;
}

int CmpClientDataByPassword(void* client, void* cmpValue)
{
	assert(ASSERTPOINTER(client) && ASSERTPOINTER(cmpValue));
	ClientInfo* c = (ClientInfo*)client;
	return strncmp(c->m_Password, (char*)cmpValue, sizeof(c->m_Password));
}

int CmpClientDataByName(void* client, void* cmpValue)
{
	assert(ASSERTPOINTER(client) && ASSERTPOINTER(cmpValue));
	ClientInfo* c = (ClientInfo*)client;
	return strncmp(c->m_Clientname, (char*)cmpValue, sizeof(c->m_Clientname));
}

void ClientSide(ManagementAPP* app)
{
	assert(ASSERTPOINTER(app));

	ListNode* client = ClientLogin(app);
	if (NULL == client)return;
	printf("Client");

}

ListNode* FindClientInfo(DoubleList* infoList)
{
	assert(ASSERTPOINTER(infoList));

	char name[20];
	char password[20];
	int erromes;
	ListNode* node = NULL;

	printf("请输入登录的用户名：\n");
	erromes = scanf("%s", name);
	CleanInputBuffer();
	if (StrInputFailure(erromes, name, sizeof(name))) {
		printf("用户名输入错误。\n");
		return NULL;
	}

	node = ListFindNode(infoList, name, CmpClientDataByName);
	if (node == ListEnd(infoList)) {
		printf("用户名不存在\n");
		return NULL;
	}

	printf("请输入登录的密码：\n");
	erromes = scanf("%s", password);
	CleanInputBuffer();
	if (StrInputFailure(erromes, password, sizeof(password))) {
		printf("密码输入错误。\n");
		return NULL;
	}

	ClientInfo* client = (ClientInfo*)node->m_Data;
	if (strncmp(client->m_Password, password, sizeof(password)) != 0) {
		printf("密码不匹配\n");
		return NULL;
	}

	return node;
}

//保存账号信息
void SaveClientInfo(void* pValue, void* operateValue)
{
	FILE* pfw = (FILE*)operateValue;
	fwrite(pValue, sizeof(ClientInfo), 1, pfw);
}

void ClientRegiste(DoubleList* infoList)
{
	assert(ASSERTPOINTER(infoList));

	ClientInfo client; //用户信息结构体
	int erromes = 0;
	ListNode* node = NULL;

	printf("请输入注册的用户名：\n");
	erromes = scanf("%s", client.m_Clientname);
	CleanInputBuffer();
	if (StrInputFailure(erromes, client.m_Clientname, sizeof(client.m_Clientname))) {
		printf("输入错误。\n");
		return;
	}

	node = ListFindNode(infoList, client.m_Clientname, CmpClientDataByName);
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
