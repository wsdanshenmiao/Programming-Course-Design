/****************************************************************************************
	Filename:		DoubleList.h
	Author:			danshenmiao
	Versions:		1.0
	Creation time:	2024.12.18
	Abstract:		可接受任意类型数据的双向循环链表
****************************************************************************************/

#pragma once
#ifndef __DOUBLYLIST__H__
#define __DOUBLYLIST__H__

#include "DSMUtil.h"

/// <summary>
/// 链表的节点，包含指向前后节点的指针和储存的数据
/// </summary>
typedef struct ListNode {
	ListNode* m_Pre;
	ListNode* m_Next;
	void* m_Data;
}ListNode;

/// <summary>
/// 链表，包含头节点、链表元素大小、内部元素的比较函数及释放内部数据内存的析构函数
/// </summary>
typedef struct DoubleList {
	ListNode* m_Head;
	size_t m_Size;
	void* (*constructor)();
	void(*destructor)(void*);
	bool (*cmpFunc)(void*, void*);
}DoubleList;

/// <summary>
/// 检测链表是否为空
/// </summary>
/// <param name="list"></param>
/// <returns></returns>
bool ListIsEmpty(const DoubleList* const list);

/// <summary>
/// 返回链表的首节点，当链表为空时返回头节点
/// </summary>
/// <param name="list"></param>
/// <returns></returns>
ListNode* Begin(const DoubleList* const list);

/// <summary>
/// 返回链表的头节点
/// </summary>
/// <param name="list"></param>
/// <returns></returns>
ListNode* End(const DoubleList* const list);

/// <summary>
/// 返回链表的头节点
/// </summary>
/// <param name="list"></param>
/// <returns></returns>
ListNode* RBegin(const DoubleList* const list);

/// <summary>
/// 返回链表的最后一个元素，当链表为空时返回头节点
/// </summary>
/// <param name="list"></param>
/// <returns></returns>
ListNode* REnd(const DoubleList* const list);

/// <summary>
/// 创建一个新的链表，需要提供分配内存的函数，析构函数及比较函数
/// </summary>
/// <param name="constructor"></param>
/// <param name="destructor"></param>
/// <param name="cmpFunc"></param>
/// <returns></returns>
DoubleList* CreateList(
	void* (*constructor)(),
	void(*destructor)(void*),
	bool (*cmpFunc)(void*, void*));

/// <summary>
/// 在链表尾端插入元素,并返回插入元素，可对该元素进行初始化
/// </summary>
/// <param name="list"></param>
ListNode* PushBack(DoubleList* list);

/// <summary>
/// 在链表头部插入元素并返回插入元素，可对该元素进行初始化
/// </summary>
/// <param name="list"></param>
ListNode* PushFront(DoubleList* list);

/// <summary>
/// 移除最后一个元素
/// </summary>
/// <param name="list"></param>
void PopBack(DoubleList* list);

/// <summary>
/// 移除第一个元素
/// </summary>
/// <param name="list"></param>
void PopFront(DoubleList* list);

/// <summary>
/// 在pos的前面插入一个元素,并返回插入元素，可对该元素进行初始化
/// </summary>
/// <param name="list"></param>
/// <param name="pos"></param>
/// <returns></returns>
ListNode* Insert(DoubleList* list, ListNode* pos);

/// <summary>
/// 移除pos处的元素，并返回其后面的元素
/// </summary>
/// <param name="list"></param>
/// <param name="pos"></param>
/// <returns></returns>
ListNode* Erase(DoubleList* list, ListNode* pos);

/// <summary>
/// 查找一个元素，并返回其所在的节点
/// </summary>
/// <param name="list"></param>
/// <param name="cmpValue"></param>
/// <returns></returns>
ListNode* Find(DoubleList* list, void* cmpValue);

/// <summary>
/// 遍历整个链表，并执行传入的操作函数
/// </summary>
/// <param name="list"></param>
/// <param name="operation"></param>	对链表内部数据进行操作的函数
/// <param name="operateValue"></param>
void Traversal(DoubleList* list, void operation(void*, void*), void* operateValue);

/// <summary>
/// 清除所有元素
/// </summary>
/// <param name="list"></param>
void Clear(DoubleList* list);

/// <summary>
/// 销毁链表，返回NULL
/// </summary>
/// <param name="list"></param>
/// <returns></returns>
DoubleList* Destroy(DoubleList* list);

/// <summary>
/// 默认的析构函数
/// </summary>
/// <param name="pValue"></param>
void DefaultDestructor(void* pValue);

#endif