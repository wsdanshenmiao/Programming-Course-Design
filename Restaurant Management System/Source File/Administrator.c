#include "Administrator.h"
#include "ManagementAPP.h"
#include "LoginSystem.h"

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

	ListNode* adminis = AdministratorLogin(app);
	if (NULL == adminis)return;

	printf("Administrator");

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

void AdministratorRegiste(DoubleList* infoList)
{
	assert(ASSERTPOINTER(infoList));

	size_t id = 0;
	char password[20] = "";
	int erromes = 0;
	ListNode* node = NULL;

	printf("请输入注册的ID：\n");
	erromes = scanf("%lld", &id);
	CleanInputBuffer();
	if (NumInputFailure(erromes)) {
		printf("输入错误。\n");
		return;
	}

	node = ListFindNode(infoList, &id, CmpAdministratorDataByID);
	if (ListEnd(infoList) != node) {
		printf("用户名已经存在\n");
		return;
	}

	printf("请输入注册的密码：\n");
	erromes = scanf("%s", password);
	CleanInputBuffer();
	if (StrInputFailure(erromes, password, sizeof(password))) {
		printf("输入错误。\n");
		return;
	}

	node = ListPushBack(infoList);	//插入对象
	AdministratorInfo* admini = (AdministratorInfo*)node->m_Data;
	admini->m_ID = id;
	strncpy(admini->m_Password, password, sizeof(password));
}