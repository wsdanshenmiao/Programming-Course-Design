#include "Administrator.h"
#include "ManagementAPP.h"
#include "LoginSystem.h"
#include "FoodInfo.h"
#include "Order.h"

// private
void AdministratorCatalogue();
ChangeAdministratorInfo(AdministratorInfo* admini);


void* CreateAdministratorData()
{
	AdministratorInfo* ad = MALLOC(AdministratorInfo);
	if (NULL == ad)return NULL;

	return (void*)ad;
}

int CmpAdministratorDataByID(void* ad0, void* id)
{
	assert(ASSERTPOINTER(ad0) && ASSERTPOINTER(id));
	size_t id0 = ((AdministratorInfo*)ad0)->m_ID;
	size_t id1 = *((size_t*)id);
	if (id0 > id1)return 1;
	else if (id0 == id1)return 0;
	else return -1;
}

int CmpAdministratorDataByPassword(void* ad, void* password)
{
	assert(ASSERTPOINTER(ad) && ASSERTPOINTER(password));
	AdministratorInfo* adminis = (AdministratorInfo*)ad;
	return strncmp(adminis->m_Password, (char*)password, sizeof(adminis->m_Password));
}

void AdministratorSide(ManagementAPP* app)
{
	assert(ASSERTPOINTER(app));

	ListNode* adminiNode = AdministratorLogin(app);
	if (NULL == adminiNode)return;
	AdministratorInfo* adini = (AdministratorInfo*)adminiNode->m_Data;

	enum AdministratorMenu {
		EXIT, SHOWMENU, ADDFOOD, REMOVEFOOD, SHOWALLORDE, PROCESSORDER, INFORMCHANGE
	};
	enum AdministratorMenu select;

	do {
		system("cls");
		AdministratorCatalogue();	//打印目录
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
			ListTraversal(app->m_FoodData, ShowFoodMenu, NULL);
			break;
		}
		case ADDFOOD: {
			// 更改菜单
			AddFood(app->m_FoodData);
			SaveInfoToFile(app->m_FoodDataFileName, app->m_FoodData, SaveFoodInfo);
			break;
		}
		case REMOVEFOOD: {
			RemoveFood(app->m_FoodData);
			SaveInfoToFile(app->m_FoodDataFileName, app->m_FoodData, SaveFoodInfo);
			break;
		}
		case SHOWALLORDE: {
			// 展示订单
			ListTraversal(app->m_OrderData, ShowAllOrder, NULL);
			break;
		}
		case PROCESSORDER: {
			ProcessOrder(app->m_OrderData, app->m_OrderDataFileName);
			SaveInfoToFile(app->m_OrderDataFileName, app->m_OrderData, SaveOrderInfo);
			break;
		}
		case INFORMCHANGE: {
			// 更改信息
			ChangeAdministratorInfo(adini);
			SaveInfoToFile(app->m_AdministratorDataFileName, app->m_AdministratorData, SaveAdministratorInfo);
			break;
		}
		default: {
			printf("输入错误。\n");
			break;
		}
		}
		if (select != EXIT) {
			CleanInputBuffer();
		}
		system("cls");
	} while (select);

}

ListNode* FindAdministratorInfo(DoubleList* infoList)
{
	assert(ASSERTPOINTER(infoList));

	size_t id;
	char password[20];
	int erromes;
	ListNode* node = NULL;

	printf("请输入登录的ID：\n");
	erromes = scanf("%lld", &id);
	CleanInputBuffer();
	if (NumInputFailure(erromes)) {
		printf("ID输入错误。\n");
		return NULL;
	}

	node = ListFindNode(infoList, &id, CmpAdministratorDataByID);
	if (node == ListEnd(infoList)) {
		printf("ID不存在\n");
		return NULL;
	}

	printf("请输入登录的密码：\n");
	erromes = scanf("%s", password);
	CleanInputBuffer();
	if (StrInputFailure(erromes, password, sizeof(password))) {
		printf("密码输入错误。\n");
		return NULL;
	}

	AdministratorInfo* ad = (AdministratorInfo*)node->m_Data;
	if (strncmp(ad->m_Password, password, sizeof(password)) != 0) {
		printf("密码不匹配\n");
		return NULL;
	}

	return node;
}

//保存账号信息
void SaveAdministratorInfo(void* pValue, void* operateValue)
{
	FILE* pfw = (FILE*)operateValue;
	fwrite(pValue, sizeof(AdministratorInfo), 1, pfw);
}

void AdministratorCatalogue()
{
	printf("**************   0.返回上一界面	********************\n");
	printf("**************   1.展示菜品		********************\n");
	printf("**************   2.加入菜品		********************\n");
	printf("**************   3.移除菜品		********************\n");
	printf("**************   4.查看订单		********************\n");
	printf("**************   5.处理订单		********************\n");
	printf("**************   6.修改管理员信息	********************\n");
}

ChangeAdministratorInfo(AdministratorInfo* admini)
{
	enum Modify {
		EXIT, ID, PASSWORD
	};
	enum Modify select;

	printf("请选择要修改的信息:\n");
	printf("0.取消修改\t\t1.ID\t\t2.密码\n");
	scanf("%d", &select);
	CleanInputBuffer();
	system("cls");
	switch (select) {
	case EXIT: {	// 退出
		break;
	}
	case ID: {
		printf("请输入新的ID：\n");
		size_t id;
		int erromes = scanf("%lld", &id);
		CleanInputBuffer();
		if (NumInputFailure(erromes)) {
			printf("输入错误。\n");
			return;
		}
		admini->m_ID = id;
		printf("修改成功。\n");
		break;
	}
	case PASSWORD: {
		ChangePassword(admini->m_Password);
		break;
	}
	default: {
		printf("输入错误。\n");
		break;
	}
	}
}
