#include "DoubleList.h"
#include "DSMUtil.h"
#include <time.h>

void _QuickSort(ListNode* start, ListNode* end, int cmp(void*, void*), bool increase);


bool AssertList(const DoubleList* const list)
{
	return NULL != list && NULL != list->m_Head;
}

bool ListIsEmpty(const DoubleList* const list)
{
	if (!AssertList(list) || NULL == list->m_Head->m_Next) return true;

	return 0 >= list->m_Size && list->m_Head->m_Next == list->m_Head;
}

ListNode* ListBegin(const DoubleList* const list)
{
	if (!AssertList(list))return NULL;

	return list->m_Head->m_Next;
}

ListNode* ListEnd(const DoubleList* const list)
{
	if (!AssertList(list))return NULL;

	return list->m_Head;
}

ListNode* ListRBegin(const DoubleList* const list)
{
	if (!AssertList(list))return NULL;

	return list->m_Head->m_Pre;
}

ListNode* ListREnd(const DoubleList* const list)
{
	if (!AssertList(list))return NULL;

	return list->m_Head;
}

DoubleList* CreateList(void* (*constructor)(), void(*destructor)(void*))
{
	assert(ASSERTPOINTER(constructor) && ASSERTPOINTER(destructor));
	DoubleList* list = MALLOC(DoubleList);
	if (NULL == list)return NULL;

	list->m_Size = 0;
	list->constructor = constructor;
	list->destructor = destructor;

	list->m_Head = MALLOC(ListNode);
	if (NULL == list->m_Head)return NULL;
	ListNode** head = &list->m_Head;
	(*head)->m_Data = NULL;
	(*head)->m_Pre = *head;
	(*head)->m_Next = *head;

	return list;
}

ListNode* ListPushBack(DoubleList* list)
{
	if (!AssertList(list))return NULL;

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

ListNode* ListPushFront(DoubleList* list)
{
	if (!AssertList(list))return NULL;

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
//	if (!AssertList(list) || ListIsEmpty(list))return;
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
//	if (!AssertList(list) || ListIsEmpty(list))return;
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

void ListPopBack(DoubleList* list)
{
	if (!AssertList(list) || ListIsEmpty(list))return;

	ListEraseNode(list, list->m_Head->m_Pre);
}

void ListPopFront(DoubleList* list)
{
	if (!AssertList(list) || ListIsEmpty(list)) return;

	ListEraseNode(list, list->m_Head->m_Next);
}

ListNode* ListInsertNode(DoubleList* list, ListNode* pos)
{
	if (!AssertList(list) || NULL == pos)return NULL;

	ListNode* newNode = MALLOC(ListNode);
	if (NULL == newNode)return NULL;

	newNode->m_Data = list->constructor();
	ListMoveNode(list, pos, newNode);
	return newNode;
}

void ListMoveNode(DoubleList* list, ListNode* pos, ListNode* node)
{
	if (!AssertList(list) || NULL == pos || NULL == node)return NULL;

	node->m_Next = pos;
	node->m_Pre = pos->m_Pre;

	pos->m_Pre->m_Next = node;
	pos->m_Pre = node;

	++list->m_Size;
}

ListNode* ListEraseNode(DoubleList* list, ListNode* pos)
{
	assert(ASSERTPOINTER(pos));
	if (!AssertList(list) || ListIsEmpty(list) || list->m_Head == pos)return NULL;

	ListNode* nextNode = pos->m_Next;
	nextNode->m_Pre = pos->m_Pre;
	pos->m_Pre->m_Next = nextNode;

	list->destructor(pos->m_Data);
	free(pos);
	pos = NULL;

	--list->m_Size;
	return nextNode;
}

ListNode* ListFindNode(DoubleList* list, void* cmpValue, int cmpFunc(void*, void*))
{
	assert(ASSERTPOINTER(cmpValue) && ASSERTPOINTER(cmpFunc));
	if (!AssertList(list) || ListIsEmpty(list))return ListEnd(list);

	ListNode* node = ListBegin(list);
	for (; node != ListEnd(list); node = node->m_Next) {
		if (0 == cmpFunc(node->m_Data, cmpValue)) break;
	}
	return node;
}

void ListTraversal(DoubleList* list, void operation(void*, void*), void* operateValue)
{
	// operateValue可以为空
	assert(ASSERTPOINTER(operation));
	if (!AssertList(list))return;

	for (ListNode* node = ListBegin(list); node != ListEnd(list); node = node->m_Next) {
		operation(node->m_Data, operateValue);
	}
}

void ListSortintIncrease(DoubleList* list, int cmpFunc(void*, void*))
{
	assert(ASSERTPOINTER(cmpFunc));
	if (!AssertList(list) || ListIsEmpty(list)) return;

	_QuickSort(list->m_Head->m_Next, list->m_Head->m_Pre, cmpFunc, true);
}

void ListSortintDecrease(DoubleList* list, int cmpFunc(void*, void*))
{
	assert(ASSERTPOINTER(cmpFunc));
	if (!AssertList(list) || ListIsEmpty(list)) return;

	_QuickSort(list->m_Head->m_Next, list->m_Head->m_Pre, cmpFunc, false);
}

void ListClear(DoubleList* list)
{
	if (!AssertList(list)) return;

	while (!ListIsEmpty(list)) {
		ListEraseNode(list, list->m_Head->m_Next);
	}
	list->m_Size = 0;
}

DoubleList* ListDestroy(DoubleList* list)
{
	if (!AssertList(list))return NULL;

	ListClear(list);
	free(list->m_Head);
	free(list);
	list = NULL;
	return list;
}

void NodeDataDefaultDestructor(void* pValue)
{
	if (NULL != pValue) {
		free(pValue);
		pValue = NULL;
	}
}

void _QuickSort(ListNode* start, ListNode* end, int cmp(void*, void*), bool increase)
{
	assert(ASSERTPOINTER(start) && ASSERTPOINTER(end) && ASSERTPOINTER(cmp));
	if (start == end)return;

	ListNode* left = start;
	ListNode* right = end;
	ListNode* preLeft = NULL;
	ListNode* preRight = NULL;
	ListNode* pivot = left;
	void* tmp = NULL;

	while (left != right) {
		while (left != right) {
			int cmpValue = cmp(right->m_Data, pivot->m_Data);
			cmpValue = increase ? cmpValue : -cmpValue;
			if (cmpValue < 0) break;

			right = right->m_Pre;
		}
		preLeft = left;
		preRight = right;
		tmp = left->m_Data;
		left->m_Data = right->m_Data;
		right->m_Data = tmp;
		if (preLeft == pivot) {
			pivot = right;
		}
		else if (preRight == pivot) {
			pivot = left;
		}

		while (left != right) {
			int cmpValue = cmp(pivot->m_Data, left->m_Data);
			cmpValue = increase ? cmpValue : -cmpValue;
			if (cmpValue < 0) break;

			left = left->m_Next;
		}
		preLeft = left;
		preRight = right;
		tmp = left->m_Data;
		left->m_Data = right->m_Data;
		right->m_Data = tmp;
		if (preLeft == pivot) {
			pivot = right;
		}
		else if (preRight == pivot) {
			pivot = left;
		}
	}
	tmp = left->m_Data;
	left->m_Data = pivot->m_Data;
	pivot->m_Data = tmp;

	if (left != start) {
		_QuickSort(start, left, cmp, increase);
	}
	if (left != end) {
		_QuickSort(left->m_Next, end, cmp, increase);
	}
}

