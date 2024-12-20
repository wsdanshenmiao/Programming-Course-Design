#include "Administrator.h"
#include "ManagementAPP.h"
#include "LoginSystem.h"

void* CreateAdministratorData()
{
	AdministratorInfo* ad = MALLOC(AdministratorInfo);
	if (NULL == ad)return NULL;

	return (void*)ad;
}

int CmpAdministratorDataByID(void* ad0, void* ad1)
{
	assert(ASSERTPOINTER(ad0) && ASSERTPOINTER(ad1));
	size_t id0 = ((AdministratorInfo*)ad0)->m_ID;
	size_t id1 = ((AdministratorInfo*)ad1)->m_ID;
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

	ListNode* adminis = AdministratorLogin(app);
	if (NULL == adminis)return;

}

ListNode* FindAdministratorInfo(DoubleList* infoList)
{
	size_t id;
	char password[20];
	int erromes;
	ListNode* node = NULL;

	printf("请输入登录的ID：\n");
	erromes = scanf("%lld", &id);
	CleanBuffer();
	if (NumInputFailure(erromes)) {
		printf("ID输入错误。\n");
		return NULL;
	}

	node = ListFindNode(infoList, id, CmpAdministratorDataByID);
	if (node == ListEnd(infoList)) {
		printf("ID不存在\n");
		return NULL;
	}

	printf("请输入登录的密码：\n");
	erromes = scanf("%s", password);
	CleanBuffer();
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
