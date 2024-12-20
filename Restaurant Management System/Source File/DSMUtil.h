/****************************************************************************************
	Filename:		DSMUtil.h
	Author:			danshenmiao
	Versions:		1.0
	Creation time:	2024.12.18
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


// general helper code
// 清除输入缓冲区
inline void CleanBuffer()
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


#endif