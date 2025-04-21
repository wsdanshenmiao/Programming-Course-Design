/*
	Versions1 ʵ��ͨ������Ļ�������
*/
/*
	Versions2 �޸�����ṹ��ģ������������������ Clear �������������� Destroy ������������
*/
/*
	Versions3 �޸� Find������Ϊ�����һ�����������������
*/
/*
	Versions4 �޸� TraversalOperation������Ϊ�����һ�����������������
*/

#ifndef __LIST__H__
#define __LIST__H__

#include <stdio.h>
#include <stdbool.h>
#include <memory.h>
#include <malloc.h>

typedef struct Node
{
	struct Node* m_Pre;
	struct Node* m_Next;
	void* m_Data;
}Node;

typedef struct List
{
	Node* m_Head;
	size_t m_Size;
	void (*deallocate)(void*);
}List;

bool IsEmpty(const List* const list);
List* InitList(void deallocate(void*));
void PushFront(List* list, const void* const pValue);
void PushBack(List* list, const void* const pValue);
void PopFront(List* list);
void PopBack(List* list);
void DefaultDeallocate(void* pValue);
Node* Insert(List* list, Node* pos, const void* const pValue);
Node* Erase(List* list, Node* pos);
Node* Find(List* list, bool findFunc(void*, void*), void* cmpValue);
void TraversalOperation(List* list, void operation(void*, void*), void* operateValue);
void Clear(List* list);
List* Destroy(List* list);


#endif // !__LIST__H__

