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


}

ListNode* FindClientInfo(DoubleList* infoList)
{
	char name[20];
	char password[20];
	int erromes;
	ListNode* node = NULL;

	printf("请输入登录的用户名：\n");
	erromes = scanf("%s", name);
	CleanBuffer();
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
	CleanBuffer();
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

