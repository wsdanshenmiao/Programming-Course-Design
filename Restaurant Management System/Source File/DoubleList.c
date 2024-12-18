#include "DoubleList.h"

#define ASSERTLIST(T) ((T)) || (((T)->m_Head))

bool ListIsEmpty(const DoubleList* const list)
{
	if (!ASSERTLIST(list)) return true;

	return 0 == list->m_Size && list->m_Head->m_Next == list->m_Head;
}

ListNode* Begin(const DoubleList* const list)
{
	if (!ASSERTLIST(list))return NULL;

	return ListIsEmpty(list) ? list->m_Head : list->m_Head->m_Next;
}

ListNode* End(const DoubleList* const list)
{
	if (!ASSERTLIST(list))return NULL;

	return list->m_Head;
}

ListNode* RBegin(const DoubleList* const list)
{
	if (!ASSERTLIST(list))return NULL;

	return list->m_Head;
}

ListNode* REnd(const DoubleList* const list)
{
	if (!ASSERTLIST(list))return NULL;

	return ListIsEmpty(list) ? list->m_Head : list->m_Head->m_Pre;
}

DoubleList* CreateList(void* (*constructor)(), void(*destructor)(void*), bool(*cmpFunc)(void*, void*))
{
	DoubleList* list = MALLOC(DoubleList);
	if (NULL == list)return NULL;

	list->m_Size = 0;
	list->constructor = constructor;
	list->destructor = destructor;
	list->cmpFunc = cmpFunc;

	ListNode** head = &list->m_Head;
	*head = MALLOC(ListNode);
	(*head)->m_Data = NULL;
	(*head)->m_Pre = *head;
	(*head)->m_Next = *head;

	return list;
}

ListNode* PushBack(DoubleList* list)
{
	if (!ASSERTLIST(list))return NULL;

	ListNode** head = &list->m_Head;

	ListNode* newNode = MALLOC(ListNode);
	if (NULL == newNode)return NULL;

	newNode->m_Data = list->constructor();
	newNode->m_Pre = (*head)->m_Pre;
	newNode->m_Next = *head;
	(*head)->m_Pre->m_Next = newNode;
	(*head)->m_Pre = newNode;

	++list->m_Size;
	return newNode;
}

ListNode* PushFront(DoubleList* list)
{
	if (!ASSERTLIST(list))return NULL;

	ListNode** head = &list->m_Head;

	ListNode* newNode = MALLOC(ListNode);
	if (NULL == newNode)return NULL;

	newNode->m_Data = list->constructor();
	newNode->m_Pre = *head;
	newNode->m_Next = (*head)->m_Next;
	(*head)->m_Next->m_Pre = newNode;
	(*head)->m_Next = newNode;

	++list->m_Size;
	return newNode;
}

//void PopBack(DoubleList* list)
//{
//	if (!ASSERTLIST(list) || ListIsEmpty(list))return;
//
//	ListNode** head = &list->m_Head;
//
//	// 清除数据
//	ListNode* deNode = (*head)->m_Pre;
//	list->destructor(deNode->m_Data);
//
//	deNode->m_Pre->m_Next = *head;
//	(*head)->m_Pre = deNode->m_Pre;
//
//	free(deNode);
//	deNode = NULL;
//
//	--list->m_Size;
//}
//
//void PopFront(DoubleList* list)
//{
//	if (!ASSERTLIST(list) || ListIsEmpty(list))return;
//
//	ListNode** head = &list->m_Head;
//
//	ListNode* deNode = (*head)->m_Next;
//	list->destructor(deNode->m_Data);
//
//	deNode->m_Next->m_Pre = *head;
//	(*head)->m_Next = deNode->m_Next;
//
//	free(deNode);
//	deNode = NULL;
//
//	--list->m_Size;
//}

void PopBack(DoubleList* list)
{
	if (!ASSERTLIST(list) || ListIsEmpty(list))return;

	Erase(list, list->m_Head->m_Pre);
}

void PopFront(DoubleList* list)
{
	if (!ASSERTLIST(list) || ListIsEmpty(list)) return;

	Erase(list, list->m_Head->m_Next);
}

ListNode* Insert(DoubleList* list, ListNode* pos)
{
	if (!ASSERTLIST(list) || NULL == pos)return NULL;

	ListNode* newNode = MALLOC(ListNode);
	if (NULL == newNode)return NULL;

	newNode->m_Data = list->constructor();
	newNode->m_Next = pos;
	newNode->m_Pre = pos->m_Pre;

	pos->m_Pre->m_Next = newNode;
	pos->m_Pre = newNode;

	++list->m_Size;
	return newNode;
}

ListNode* Erase(DoubleList* list, ListNode* pos)
{
	if (!ASSERTLIST(list) || ListIsEmpty(list) ||
		NULL == pos || list->m_Head == pos)return NULL;

	ListNode* nextNode = pos->m_Next;
	nextNode->m_Pre = pos->m_Pre;
	pos->m_Pre = nextNode;

	list->destructor(pos->m_Data);
	free(pos);
	pos = NULL;

	--list->m_Size;
	return nextNode;
}

ListNode* Find(DoubleList* list, void* cmpValue)
{
	if (!ASSERTLIST(list) || NULL == cmpValue)return NULL;

	ListNode* node = Begin(list);
	for (; node != End(list); node = node->m_Next) {
		if (0 == list->cmpFunc(node->m_Data, cmpValue)) break;
	}
	return node;
}

void Traversal(DoubleList* list, void operation(void*, void*), void* operateValue)
{
	if (!ASSERTLIST(list) || NULL == operation)return;

	for (ListNode* node = Begin(list); node != End(list); node = node->m_Next) {
		operation(node->m_Data, operateValue);
	}
}

void Clear(DoubleList* list)
{
	if (!ASSERTLIST(list)) return;

	while (!ListIsEmpty(list)) {
		PopFront(list);
	}
	list->m_Size = 0;
}

DoubleList* Destroy(DoubleList* list)
{
	if (!ASSERTLIST(list))return NULL;

	Clear(list);
	free(list->m_Head);
	free(list);
	list = NULL;
	return list;
}

void DefaultDestructor(void* pValue)
{
	if (NULL != pValue) {
		free(pValue);
		pValue = NULL;
	}
}



