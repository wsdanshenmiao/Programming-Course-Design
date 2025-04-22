#define _CRT_SECURE_NO_WARNINGS

#include "Util.h"

void CleanBuffer()
{
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}

// �ַ��������⣬����ʧ�ܷ���true/1
bool StrInputFailure(int erromes, char* name, size_t size)
{
	if (!name) {
		return true;
	}
	size_t len = strnlen(name, size);
	if (!erromes || erromes == EOF || len == 0 || len >= size) {
		return true;
	}
	return false;
}

// ���������⣬����ʧ�ܷ���true/1
bool NumInputFailure(int erromes)
{
	if (!erromes || erromes == EOF) {
		return true;
	}
	return false;
}



void SaveUserinfoFunc(void* pValue, void* operateValue)
{
	FILE* pfw = (FILE*)operateValue;
	fwrite(pValue, sizeof(Userinfo), 1, pfw);
}
//�����˺���Ϣ
void SaveUserinfo()
{
	FILE* pfw = fopen("Userinfo.dat", "wb");	//�����ļ�
	if (pfw == NULL) {
		printf("%s", strerror(errno));
		return;
	}
	TraversalOperation(g_Userinfo, SaveUserinfoFunc, pfw);
	fclose(pfw);
}

// ���涩��
void SaveOrderFormFunc(void* pValue, void* operateValue)
{
	FILE* pfw = (FILE*)operateValue;
	fwrite(pValue, sizeof(OrderForm), 1, pfw);
}
void SaveOrderForm()
{
	FILE* opfw = fopen("OrderForm.dat", "wb");	//�����ļ�
	if (opfw == NULL) {
		printf("%s", strerror(errno));
		return;
	}
	TraversalOperation(g_OrderForm, SaveOrderFormFunc, opfw);
	fclose(opfw);
}

// ������Ʒ��Ϣ
void SaveCommodityFunc(void* pValue, void* operateValue)
{
	FILE* pfw = (FILE*)operateValue;
	fwrite(pValue, sizeof(Commodity), 1, pfw);
}
void SaveCommodity()
{
	FILE* cpfw = fopen("Commodity.dat", "wb");	//�����ļ�
	if (cpfw == NULL) {
		printf("%s", strerror(errno));
		return;
	}
	TraversalOperation(g_Commodity, SaveCommodityFunc, cpfw);
	fclose(cpfw);
}


// ��ӡ��������
void PrintOrderForm(void* pValue, void* operateValue)
{
	OrderForm* orderForm = (OrderForm*)(pValue);
	printf("������ţ�%zu\t��Ʒ���ƣ�%s\t����������%zu\t�����ܼۣ�%zu\tδ��������%zu\t����������%zu\t���û�����%s\n�򷽵绰��%s\t�򷽵�ַ��%s\t����״̬��%s\n",
		orderForm->m_OrderNumber, orderForm->m_CommodityName,
		orderForm->m_CommodityNum, orderForm->m_CommodityPrices,
		orderForm->m_UndeliverNum, orderForm->m_DeliverNum,
		orderForm->m_UserName, orderForm->m_UserPhoneNum,
		orderForm->m_UserAddress, orderForm->m_OrderStatus);
	printf("\n-----------------------------------------------------------------------------------------------\n");
}

// ��ӡ��Ʒ
void PrintCommofity(void* pValue, void* operateValue)
{
	Commodity* commofity = (Commodity*)(pValue);
	printf("���ƣ�%s\t���ۣ�%zu\n",
		commofity->m_CommodityName,
		commofity->m_CommodityPrices);
}

// ��ӡȫ���˺���Ϣ
void PrintUserAll(void* pValue, void* operateValue)
{
	Userinfo* userinfo = (Userinfo*)pValue;
	printf("�û�����%s\t ���룺%s\t �绰��%s\t ��ַ��%s\t ��%zu\n",
		userinfo->m_Username,
		userinfo->m_Password,
		userinfo->m_UserPhoneNum,
		userinfo->m_Address,
		userinfo->m_Balance);
}

// ��ӡ�˺���Ϣ,����û����ʾ�˺ŵ�����
void PrintUser(void* pValue, void* operateValue)
{
	Userinfo* userinfo = (Userinfo*)pValue;
	printf("%s\t%s\t%s\t%lld\n",
		userinfo->m_Username,
		userinfo->m_UserPhoneNum,
		userinfo->m_Address,
		userinfo->m_Balance);
}


bool IsNumber(const char* str, size_t num)
{
	if (!str) {
		return false;
	}
	for (int i = 0; i < num; ++i) {
		if ('0' > str[i] || str[i] > '9') {
			return false;
		}
	}
	return true;
}

bool IsAllAlphaNumeric(const char* str, size_t num)
{
	// ���ָ���Ƿ�Ϊ��
	if (str == NULL) {
		return false;
	}
	// �����ַ���ֱ���������ַ� '\0'
	for (size_t i = 0; str[i] != '\0' && i < num; ++i) {
		// �����ǰ�ַ�������ĸ�������ַ������� false
		if (!('0' <= str[i] && str[i] <= '9') &&
			!('a' <= str[i] && str[i] <= 'z') &&
			!('z' <= str[i] && str[i] <= 'Z')) {
			return false;
		}
	}
	// ��������ַ�������ĸ�������ַ������� true
	return true;
}