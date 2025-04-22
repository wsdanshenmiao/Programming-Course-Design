#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "User.h"
#include "Merchant.h"
#include "Util.h"
#include "List.h"
#include "GlobalVariable.h"

#define MALLOC(T) ((T*)malloc(sizeof(T)))


void* InitOrderForm()
{
	return MALLOC(OrderForm);
}

void* InitUserinfo()
{
	return MALLOC(Userinfo);
}

void* InitCommodity()
{
	return MALLOC(Commodity);
}

bool InitInformation()
{
	g_OrderForm = InitList(DefaultDeallocate);
	g_Userinfo = InitList(DefaultDeallocate);
	g_Commodity = InitList(DefaultDeallocate);
	List** pList[3] = {
		&g_OrderForm,
		&g_Userinfo,
		&g_Commodity
	};
	const char* fileName[3] = {
		"OrderForm.dat",
		"Userinfo.dat",
		"Commodity.dat"
	};
	void* (*func[3])() = {
		InitOrderForm,
		InitUserinfo,
		InitCommodity
	};
	size_t size[3] = {
		sizeof(OrderForm),
		sizeof(Userinfo),
		sizeof(Commodity)
	};
	for (int i = 0; i < 3; i++) {
		List** list = pList[i];
		FILE* pfr;
		if (_access(fileName[i], 0)) {
			pfr = fopen(fileName[i], "wb");
		}
		else {
			pfr = fopen(fileName[i], "rb");
		}
		void* value = func[i]();
		if (!value) {
			return false;
		}
		for (; fread(value, size[i], 1, pfr); ) {
			PushFront(*list, value);
			value = func[i]();
			if (!value) {
				return false;
			}
		}
		free(value);
		value = NULL;
		fclose(pfr);
	}
	return true;
}

void DestroyData()
{
	Destroy(g_Commodity);
	Destroy(g_OrderForm);
	Destroy(g_Userinfo);
}

void MasterCatalogue()
{
	printf("欢迎使用订水信息管理系统，请输入数字选择想要进行的操作\n");
	printf("*****************  0.退出程序     ********************\n");
	printf("*****************  1.用户通道     ********************\n");
	printf("*****************  2.商家通道     ********************\n");
}

void MasterUI()
{
	enum MasterMenu {
		EXIT, USER, MERCHANT
	};
	enum MasterMenu select;
	do {
		MasterCatalogue();	//打印目录
		printf("请选择:");
		scanf("%d", &select);
		CleanBuffer();
		system("cls");
		switch (select) {
		case EXIT:
			SaveCommodity();
			SaveOrderForm();
			SaveUserinfo();
			break;
		case USER: {
			UserUI();
			break;
		}
		case MERCHANT: {
			MerchantUI();
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
}


int main()
{
	if (!InitInformation()) {
		return 0;
	}
	MasterUI();
	DestroyData();
	return 0;
}