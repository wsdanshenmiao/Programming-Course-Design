#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "GlobalVariable.h"
#include "LoginSystem.h"
#include "Merchant.h"
#include "User.h"
#include "Util.h"
#include "List.h"

#define MALLOC(T) ((T*)malloc(sizeof(T)))

//typedef struct Object
//{
//	char name[10];
//	char phone[10];
//	int age;
//}Object;
//
//bool FindFunc(void* pValue, void* cmpValue)
//{
//	return ((Object*)pValue)->age == *((int*)cmpValue);
//}
//
//void Operation(void* pValue, void* operateValue)
//{
//	Object* object = (Object*)pValue;
//	printf("%s\t%s\t%d\n", object->name, object->phone, object->age);
//}
//
//void test()
//{
//	List* list = InitList(DefaultDeallocate);
//
//	printf("%d\n", IsEmpty(list));
//
//	for (int i = 0; i < 5; i++) {
//		Object* object1 = MALLOC(Object);
//		object1->age = i;
//		strncpy(object1->name, "CL", sizeof("CL"));
//		strncpy(object1->phone, "123", sizeof("123"));
//		PushFront(list, object1);
//	}
//	printf("size: %lld\n", list->m_Size);
//	TraversalOperation(list, Operation, NULL);
//	printf("-----------------------------\n");
//
//	for (int i = 0; i < 5; i++) {
//		Object* object1 = MALLOC(Object);
//		object1->age = i;
//		strncpy(object1->name, "AB", sizeof("AB"));
//		strncpy(object1->phone, "456", sizeof("456"));
//		PushBack(list, object1);
//	}
//	printf("size: %lld\n", list->m_Size);
//	TraversalOperation(list, Operation, NULL);
//	printf("-----------------------------\n");
//
//	printf("%d\n", IsEmpty(list));
//
//	PopFront(list);
//	PopFront(list);
//	TraversalOperation(list, Operation, NULL);
//	printf("-----------------------------\n");
//
//	PopBack(list);
//	PopBack(list);
//	TraversalOperation(list, Operation, NULL);
//	printf("size: %lld\n", list->m_Size);
//	printf("-----------------------------\n");
//
//	int cmpValue = 0;
//	Node* node = Find(list, FindFunc, &cmpValue);
//	printf("%d\n", ((Object*)node->m_Data)->age);
//	for (int i = 0; i < 5; i++) {
//		Object* object1 = MALLOC(Object);
//		object1->age = i;
//		strncpy(object1->name, "AB", sizeof("AB"));
//		strncpy(object1->phone, "456", sizeof("456"));
//		Insert(list, node, object1);	
//	}
//	TraversalOperation(list, Operation, NULL);
//	printf("-----------------------------\n");
//
//	for (int i = 0; i < 5; i++) {
//		Node* next = node->m_Next;
//		Erase(list, node);	//注意别把头节点传进去了，传进去不会做任何事
//		node = next;
//	}
//	TraversalOperation(list, Operation, NULL);
//	printf("-----------------------------\n");
//
//	Clear(list);
//	TraversalOperation(list, Operation, NULL);
//	printf("size: %lld\n", list->m_Size);
//	list = Destroy(list);
//}
//

//int main()
//{
//	test();
//	return 0;
//}