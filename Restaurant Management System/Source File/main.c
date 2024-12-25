#include "ManagementAPP.h"
#include "Administrator.h"
#include <time.h>

void test();

int main()
{
	//test();
	ManagementAPP* app = MALLOC(ManagementAPP);
	int errorInfo = 0;
	if (NULL == app) {
		return -1;
	}
	if (InitManagementAPP(app)) {
		errorInfo = 0 == RunManagementAPP(app) ? 0 : -1;
		ExitManagementAPP(app);
	}
	else {
		errorInfo = -1;
	}
	free(app);
	app = NULL;
	return errorInfo;
}

void test()
{
	srand((unsigned)time(NULL));
	DoubleList* list = CreateList(CreateAdministratorData, NodeDataDefaultDestructor);
	for (int i = 1000; i > 0; --i) {
		ListNode* node = ListPushBack(list);
		AdministratorInfo* data = (AdministratorInfo*)node->m_Data;
		data->m_ID = rand();
	}
	//for (ListNode* it = ListBegin(list); it != ListEnd(list); it = it->m_Next) {
	//	AdministratorInfo* data = (AdministratorInfo*)it->m_Data;
	//	printf("%lld ", data->m_ID);
	//}
	printf("\n");
	ListSortintIncrease(list, CmpAdministratorDataByID);
	//for (ListNode* it = ListBegin(list); it != ListEnd(list); it = it->m_Next) {
	//	AdministratorInfo* data = (AdministratorInfo*)it->m_Data;
	//	printf("%lld ", data->m_ID);
	//}
	printf("\n");
}
