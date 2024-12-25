#include "Client.h"
#include "ManagementAPP.h"
#include "LoginSystem.h"
#include "Order.h"
#include "FoodInfo.h"

// private
void ClientCatalogue();
void Recharge(ClientInfo* client);
void ChangeClientInfo(ClientInfo* client);


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
	return strncmp(c->m_ClientName, (char*)cmpValue, sizeof(c->m_ClientName));
}

void ClientSide(ManagementAPP* app)
{
	assert(ASSERTPOINTER(app));

	ListNode* clientNode = ClientLogin(app);
	if (NULL == clientNode)return;

	ClientInfo* client = (ClientInfo*)clientNode->m_Data;

	enum ClientMenu {
		EXIT, SHOWMENU, ORDERDISHES, SHOWORDE, RECHARGE, INFORMCHANGE
	};
	enum ClientMenu select;

	do {
		system("cls");
		ClientCatalogue();	//打印目录
		printf("请选择:");
		scanf("%d", &select);
		CleanInputBuffer();
		system("cls");
		switch (select) {
		case EXIT: {
			break;
		}
		case SHOWMENU: {
			// 展示菜单
			ShowFoodMenu(app->m_FoodData);
			break;
		}
		case ORDERDISHES: {
			// 点餐
			OrderDishes(app, clientNode->m_Data);
			SaveInfoToFile(app->m_OrderDataFileName, app->m_OrderData, SaveOrderInfo);
			break;
		}
		case SHOWORDE: {
			// 展示已点菜单
			ListTraversal(app->m_OrderData, ShowOrder, client->m_ClientName);
			break;
		}
		case RECHARGE: {
			// 充值
			Recharge(clientNode->m_Data);
			SaveInfoToFile(app->m_ClientDataFileName, app->m_ClientData, SaveClientInfo);
			break;
		}
		case INFORMCHANGE: {
			// 更改信息
			ChangeClientInfo(clientNode->m_Data);
			SaveInfoToFile(app->m_ClientDataFileName, app->m_ClientData, SaveClientInfo);
			break;
		}
		default: {
			printf("输入错误。\n");
			break;
		}
		}
		if (select != EXIT && select != SHOWMENU) {
			CleanInputBuffer();
		}
		system("cls");
	} while (select);
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

void ShowClientNameAndPhoneNum(void* pValue, void* pad)
{
	assert(ASSERTPOINTER(pValue));

	ClientInfo* client = (ClientInfo*)pValue;
	printf("客户名字：%s\n", client->m_ClientName);
	printf("客户电话号：%s\n", client->m_ClientPhoneNum);
}

void ShowClientAllInfo(void* pValue, void* pad)
{
	assert(ASSERTPOINTER(pValue));

	ClientInfo* client = (ClientInfo*)pValue;
	printf("客户名字：%s\n", client->m_ClientName);
	printf("客户密码：%s\n", client->m_Password);
	printf("客户电话号：%s\n", client->m_ClientPhoneNum);
	printf("客户余额：%lld\n", client->m_Balance);
}

void ClientCatalogue()
{
	printf("*****************	0.返回主界面		********************\n");
	printf("*****************	1.展示菜单		********************\n");
	printf("*****************	2.点餐			********************\n");
	printf("*****************	3.查看已点菜餐	********************\n");
	printf("*****************	4.账户充值		********************\n");
	printf("*****************	5.资料修改		********************\n");
}

void Recharge(ClientInfo* client)
{
	size_t amount;
	printf("当前余额：%zu\n", client->m_Balance);
	printf("请输入充值金额：\n");
	int error = scanf("%zu", &amount); // 获取用户输入的充值金额
	CleanInputBuffer();
	if (NumInputFailure(error)) { // 检查输入是否失败
		printf("输入错误，请重新输入。\n");
		return;
	}


	client->m_Balance += amount;
	printf("充值成功，当前余额：%zu\n", client->m_Balance); // 充值成功，打印当前余额
	getchar();
}

void ChangeClientInfo(ClientInfo* client)
{
	ShowClientAllInfo(client, NULL);
	enum Modify {
		EXIT, NAME, PASSWORD, PHONENUMBER
	};
	enum Modify select;

	printf("请选择要修改的信息:\n");
	printf("0.取消修改\t\t1.名字\t\t2.密码\t\t3.手机号\n");
	scanf("%d", &select);
	CleanInputBuffer();
	system("cls");
	switch (select) {
	case EXIT: {	// 退出
		break;
	}
	case NAME: {
		printf("请输入新的名字：\n");
		char name[20];
		int erromes = scanf("%s", name);
		CleanInputBuffer();
		if (StrInputFailure(erromes, name, sizeof(name))) {
			printf("输入错误。\n");
			return;
		}
		strncpy(client->m_ClientName, name, sizeof(name));
		printf("修改成功。\n");
		break;
	}
	case PASSWORD: {
		ChangePassword(client->m_Password);
		break;
	}
	case PHONENUMBER: {
		printf("请输入新的手机号：\n");
		char phoneNum[20];
		int erromes = scanf("%s", phoneNum);
		CleanInputBuffer();
		if (StrInputFailure(erromes, phoneNum, sizeof(phoneNum)) || !IsNumber(phoneNum, strlen(phoneNum))) {
			printf("输入错误。\n");
			return;
		}
		strncpy(client->m_ClientPhoneNum, phoneNum, sizeof(phoneNum));
		printf("修改成功。\n");
		break;
	}
	default: {
		printf("输入错误。\n");
		break;
	}
	}
}
