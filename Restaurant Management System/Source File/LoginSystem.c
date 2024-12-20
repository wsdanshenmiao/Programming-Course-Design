#include "LoginSystem.h"
#include "ManagementAPP.h"
#include "Client.h"
#include "Administrator.h"

// private
void ClientRegister();

void AdministratorRegister();


ListNode* ManagementAPPLogin(
	DoubleList* infoList,
	ListNode* findInfo(DoubleList*),
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
		CleanBuffer();
		system("cls");
		switch (select) {
		case EXIT: {	//保存信息并退出
			FILE* pfw = fopen("Userinfo.dat", "wb");	//创建文件
			if (pfw == NULL) {
				printf("%s", strerror(errno));
				return;
			}
			//TODO:遍历信息链表保存信息

			fclose(pfw);
			break;
		}
		case REGISTER: {  //注册

			getchar();
			break;
		}
		case LOGIN: {	//登录
			ListNode* node = findInfo(infoList);
			if (!node) {
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
	return ManagementAPPLogin(app->m_ClientData, FindClientInfo, catalogue);
}

void ClientRegister()
{
}




ListNode* AdministratorLogin(ManagementAPP* app)
{
	assert(ASSERTPOINTER(app));
	char* catalogue =
		"**************   0.返回主界面     ********************\n"
		"**************   1.管理员注册     ********************\n"
		"**************   2.管理员登录     ********************\n";
	return ManagementAPPLogin(app->m_AdministratorData, FindAdministratorInfo, catalogue);
}

void AdministratorRegister()
{
}

