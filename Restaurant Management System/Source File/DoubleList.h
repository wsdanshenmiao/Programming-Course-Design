/****************************************************************************************
	Filename:		DoubleList.h
	Author:			danshenmiao
	Versions:		1.0
	Creation time:	2024.12.18
	Finish time:	2024.12.18
	Abstract:		可接受任意类型数据的双向循环链表
****************************************************************************************/
/****************************************************************************************
	Filename:		DoubleList.h
	Author:			danshenmiao
	Versions:		2.0
	Creation time:	2024.12.20
	Finish time:	2024.12.20
	Abstract:		更改接口名称，加入断言指针,修复Erase的问题
****************************************************************************************/

#ifndef __DOUBLELIST__H__
#define __DOUBLELIST__H__

#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(T) ((T*)malloc(sizeof(T)))
#define ASSERTPOINTER(T) (NULL != (T))


#include <stdbool.h>
#include <malloc.h>
#include <assert.h>

/// <summary>
/// 链表的节点，包含指向前后节点的指针和储存的数据
/// </summary>
typedef struct ListNode {
	struct ListNode* m_Pre;
	struct ListNode* m_Next;
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
}DoubleList;

bool AssertList(const DoubleList* const list);


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
ListNode* ListBegin(const DoubleList* const list);


/// <summary>
/// 返回链表的头节点
/// </summary>
/// <param name="list"></param>
/// <returns></returns>
ListNode* ListEnd(const DoubleList* const list);


/// <summary>
/// 返回链表的头节点
/// </summary>
/// <param name="list"></param>
/// <returns></returns>
ListNode* ListRBegin(const DoubleList* const list);


/// <summary>
/// 返回链表的最后一个元素，当链表为空时返回头节点
/// </summary>
/// <param name="list"></param>
/// <returns></returns>
ListNode* ListREnd(const DoubleList* const list);


/// <summary>
/// 创建一个新的链表，需要提供分配内存的函数，析构函数及比较函数
/// </summary>
/// <param name="constructor"></param>
/// <param name="destructor"></param>
/// <returns></returns>
DoubleList* CreateList(
	void* (*constructor)(),
	void(*destructor)(void*));


/// <summary>
/// 在链表尾端插入元素,并返回插入元素，可对该元素进行初始化
/// </summary>
/// <param name="list"></param>
ListNode* ListPushBack(DoubleList* list);


/// <summary>
/// 在链表头部插入元素并返回插入元素，可对该元素进行初始化
/// </summary>
/// <param name="list"></param>
ListNode* ListPushFront(DoubleList* list);


/// <summary>
/// 移除最后一个元素
/// </summary>
/// <param name="list"></param>
void ListPopBack(DoubleList* list);


/// <summary>
/// 移除第一个元素
/// </summary>
/// <param name="list"></param>
void ListPopFront(DoubleList* list);


/// <summary>
/// 在pos的前面插入一个元素,并返回插入元素，可对该元素进行初始化
/// </summary>
/// <param name="list"></param>
/// <param name="pos"></param>
/// <returns></returns>
ListNode* ListInsertNode(DoubleList* list, ListNode* pos);


/// <summary>
/// 移除pos处的元素，并返回其后面的元素
/// </summary>
/// <param name="list"></param>
/// <param name="pos"></param>
/// <returns></returns>
ListNode* ListEraseNode(DoubleList* list, ListNode* pos);


/// <summary>
/// 查找一个元素，并返回其所在的节点
/// </summary>
/// <param name="list"></param>
/// <param name="cmpValue"></param>
/// <returns></returns>
ListNode* ListFindNode(DoubleList* list, void* cmpValue, int cmpFunc(void*, void*));


/// <summary>
/// 遍历整个链表，并执行传入的操作函数
/// </summary>
/// <param name="list"></param>
/// <param name="operation"></param>	对链表内部数据进行操作的函数
/// <param name="operateValue"></param>
void ListTraversal(DoubleList* list, void operation(void*, void*), void* operateValue);


/// <summary>
/// 清除所有元素
/// </summary>
/// <param name="list"></param>
void ListClear(DoubleList* list);


/// <summary>
/// 销毁链表，返回NULL
/// </summary>
/// <param name="list"></param>
/// <returns></returns>
DoubleList* ListDestroy(DoubleList* list);


/// <summary>
/// 默认的析构函数
/// </summary>
/// <param name="pValue"></param>
void NodeDataDefaultDestructor(void* pValue);

#endif