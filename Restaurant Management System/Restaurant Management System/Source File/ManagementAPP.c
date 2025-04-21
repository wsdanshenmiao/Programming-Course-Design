#include "ManagementAPP.h"
#include "Administrator.h"
#include "Client.h"
#include "FoodInfo.h"
#include "Order.h"
#include "LoginSystem.h"

// private
void MasterCatalogue();
bool ReadDataFromFile(ManagementAPP* app);



bool InitManagementAPP(ManagementAPP* app)
{
	assert(ASSERTPOINTER(app));
	app->m_AdministratorData = CreateList(CreateAdministratorData, NodeDataDefaultDestructor);
	app->m_ClientData = CreateList(CreateClientData, NodeDataDefaultDestructor);
	app->m_FoodData = CreateList(CreateFoodInfoData, NodeDataDefaultDestructor);
	app->m_OrderData = CreateList(CreateOrderInfoData, NodeDataDefaultDestructor);
	if (!ASSERTPOINTER(app->m_AdministratorData) ||
		!ASSERTPOINTER(app->m_ClientData) ||
		!ASSERTPOINTER(app->m_FoodData) ||
		!ASSERTPOINTER(app->m_OrderData))return false;

	strncpy(app->m_AdministratorDataFileName,
		"AdministratorData.dat",
		sizeof(app->m_AdministratorDataFileName));
	strncpy(app->m_ClientDataFileName,
		"ClientData.dat",
		sizeof(app->m_ClientDataFileName));
	strncpy(app->m_FoodDataFileName,
		"FoodData.dat",
		sizeof(app->m_FoodDataFileName));
	strncpy(app->m_OrderDataFileName,
		"OrderData.dat",
		sizeof(app->m_OrderDataFileName));

	return ReadDataFromFile(app);
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
		CleanInputBuffer();
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
	app->m_FoodData = ListDestroy(app->m_FoodData);
	app->m_OrderData = ListDestroy(app->m_OrderData);
}




void MasterCatalogue()
{
	printf("*****************  0.退出程序     ********************\n");
	printf("*****************  1.用户通道     ********************\n");
	printf("*****************  2.商家通道     ********************\n");
}

bool ReadDataFromFile(ManagementAPP* app)
{
	assert(ASSERTPOINTER(app));

	DoubleList** pList[3] = {
		&(app->m_AdministratorData),
		&(app->m_ClientData),
		&(app->m_FoodData),
	};
	const char* fileName[3] = {
		app->m_AdministratorDataFileName,
		app->m_ClientDataFileName,
		app->m_FoodDataFileName,
	};
	void* (*func[3])() = {
		CreateAdministratorData,
		CreateClientData,
		CreateFoodInfoData,
	};
	size_t size[3] = {
		sizeof(AdministratorInfo),
		sizeof(ClientInfo),
		sizeof(FoodInfo),
	};

	for (int i = 0; i < 3; i++) {
		DoubleList** list = pList[i];
		FILE* pfr;
		if (_access(fileName[i], 0)) {
			pfr = fopen(fileName[i], "wb");
		}
		else {
			pfr = fopen(fileName[i], "rb");
		}
		void* value = func[i]();
		if (NULL == value) {
			return false;
		}
		for (; fread(value, size[i], 1, pfr); ) {
			ListNode* node = ListPushBack(*list);
			memcpy(node->m_Data, value, size[i]);
		}
		free(value);
		value = NULL;
		fclose(pfr);
	}

	return ReadOrderInfo(app);
}
