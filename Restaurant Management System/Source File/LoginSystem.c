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
			SaveUserInfo(fileName, infoList, saveInfo);
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
		CleanInputBuffer();
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

void SaveUserInfo(char* fileName, DoubleList* infoList, void saveInfo(void*, void*))
{
	FILE* pfw = fopen(fileName, "wb");	//创建文件
	if (pfw == NULL) {
		printf("%s", strerror(errno));
		return;
	}
	// 遍历信息链表保存信息
	ListTraversal(infoList, saveInfo, pfw);
	fclose(pfw);
}
