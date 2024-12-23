/****************************************************************************************
	Filename:		DSMUtil.h
	Author:			danshenmiao
	Versions:		1.0
	Creation time:	2024.12.18
	Finish time:	2024.12.22
	Abstract:		通用辅助函数
****************************************************************************************/


#ifndef __DSMUTIL__H__
#define __DSMUTIL__H__

// macro
#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(T) ((T*)malloc(sizeof(T)))
#define ASSERTPOINTER(T) (NULL != (T))

// include standard header
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <memory.h>
#include <malloc.h>
#include <io.h>
#include <Windows.h>

#include "DoubleList.h"

// general helper code
// 清除输入缓冲区
inline void CleanInputBuffer()
{
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}

// 字符串输入检测，输入失败返回true
inline bool StrInputFailure(int erromes, char* name, size_t size)
{
	if (!ASSERTPOINTER(name)) {
		return true;
	}
	size_t len = strnlen(name, size);
	return (!erromes || erromes == EOF || len == 0 || len >= size) ? true : false;
}

// 数字输入检测，输入失败返回true
inline bool NumInputFailure(int erromes)
{
	return (0 == erromes || EOF == erromes) ? true : false;
}

inline bool IsNumber(const char* str, size_t num)
{
	assert(ASSERTPOINTER(str));

	for (int i = 0; i < num; ++i) {
		if (!isalnum(str[i])) {
			return false;
		}
	}
	return true;
}

inline void ChangePassword(char* pPassword)
{
	printf("请输入新的密码：\n");
	char password1[20];
	int erromes = scanf("%s", password1);
	CleanInputBuffer();
	if (StrInputFailure(erromes, password1, sizeof(password1)) || !IsNumber(password1, strlen(password1))) {
		printf("输入错误。\n");
		return;
	}

	printf("请确认新的密码：\n");
	char password2[20];
	erromes = scanf("%s", password2);
	CleanInputBuffer();
	if (StrInputFailure(erromes, password2, sizeof(password2)) || !IsNumber(password2, strlen(password2))) {
		printf("输入错误。\n");
		return;
	}
	if (strncmp(password1, password2, sizeof(password1)) == 0) {
		strncpy(pPassword, password2, sizeof(password2));
		printf("修改成功。\n");
	}
	else {
		printf("输入不相同。\n");
		return;
	}
}

/// <summary>
/// 保存信息到文件
/// </summary>
/// <param name="fileName"></param>	文件的名字
/// <param name="infoList"></param>	所要保存的链表
/// <param name="saveInfo"></param>	保存信息的回调函数
inline void SaveInfoToFile(char* fileName, DoubleList* infoList, void saveInfo(void*, void*))
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

#endif