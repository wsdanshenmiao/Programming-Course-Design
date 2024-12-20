#include "ManagementAPP.h"
#include "Administrator.h"
#include "Client.h"
#include "FoodInfo.h"
#include "Order.h"
#include "LoginSystem.h"

// private
void MasterCatalogue();


bool InitManagementAPP(ManagementAPP* app)
{
	assert(ASSERTPOINTER(app));
	app->m_AdministratorData = CreateList(CreateAdministratorData, NodeDataDefaultDestructor);
	app->m_ClientData = CreateList(CreateClientData, NodeDataDefaultDestructor);
	app->m_FoodMenu = CreateList(CreateFoodMenuData, NodeDataDefaultDestructor);
	app->m_OrderData = CreateList(CreateOrderInfoData, NodeDataDefaultDestructor);
	if (!ASSERTPOINTER(app->m_AdministratorData) ||
		!ASSERTPOINTER(app->m_ClientData) ||
		!ASSERTPOINTER(app->m_FoodMenu) ||
		!ASSERTPOINTER(app->m_OrderData))return false;
	else return true;
}

int RunManagementAPP(ManagementAPP* app)
{
	assert(ASSERTPOINTER(app));

	enum MasterMenu {
		EXIT = 0, CLIENT = 1, ADMINISTRATOR = 2
	};
	enum MasterMenu select;
	do {
		MasterCatalogue();	//打印目录
		printf("请选择:");
		int errMes = scanf("%d", &select);
		CleanBuffer();
		system("cls");
		switch (select) {
		case EXIT:

			break;
		case CLIENT: {
			ClientSide(app);
			break;
		}
		case ADMINISTRATOR: {
			AdministratorSide(app);
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


	return 0;
}

void ExitManagementAPP(ManagementAPP* app)
{
	assert(ASSERTPOINTER(app));
	app->m_AdministratorData = ListDestroy(app->m_AdministratorData);
	app->m_ClientData = ListDestroy(app->m_ClientData);
	app->m_FoodMenu = ListDestroy(app->m_FoodMenu);
	app->m_OrderData = ListDestroy(app->m_OrderData);
}




void MasterCatalogue()
{
	printf("*****************  0.退出程序     ********************\n");
	printf("*****************  1.用户通道     ********************\n");
	printf("*****************  2.商家通道     ********************\n");
}
