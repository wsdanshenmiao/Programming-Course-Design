#include "List.h"

#define MALLOC(T) ((T*)malloc(sizeof(T)))
#define ASSERTLIST(T) if ((!(T)) || (!((T)->m_Head))) {return;}
#define ASSERTNODE(T) if (!(T)) {return;}

//Public

/*
*  @description : 判断链表是否为空
*  @param		: list为链表
*  @return		: 为空时返回true
*/
bool IsEmpty(const List* const list)
{
	return list->m_Size == 0 && list->m_Head->m_Next == list->m_Head;
}

/*
*  @description : 初始化链表
*  @param		: None
*  @return		: 指向链表的指针
*/
List* InitList(void deallocate(void*))
{
	List* list = MALLOC(List);
	if (!list) {
		return NULL;
	}
	Node* head = MALLOC(Node);
	if (!head) {
		return NULL;
	}
	head->m_Data = NULL;	//初始化头节点
	head->m_Next = head;
	head->m_Pre = head;
	list->m_Head = head;	//初始化链表
	list->m_Size = 0;
	list->deallocate = deallocate;
	return list;
}

/*
*  @description : 头端插入元素，传入已经分配好内存的数据
*  @param		: list链表, pValue数据的地址
*  @return		: None
*/
void PushFront(List* list, const void* const pValue)
{
	ASSERTLIST(list);
	Node* head = list->m_Head;
	Node* node = MALLOC(Node);
	ASSERTNODE(node);
	node->m_Data = pValue;	//接管数据
	node->m_Pre = head;	//插入节点
	node->m_Next = head->m_Next;
	head->m_Next->m_Pre = node;
	head->m_Next = node;
	list->m_Size++;	//容量增加
}

/*
*  @description : 尾部插入元素，传入已经分配好内存的数据
*  @param		: list链表, pValue数据的地址
*  @return		: None
*/
void PushBack(List* list, const void* const pValue)
{
	ASSERTLIST(list);
	Node* head = list->m_Head;
	Node* node = MALLOC(Node);
	ASSERTNODE(node);
	node->m_Data = pValue;	//接管数据
	node->m_Next = head;	//插入节点
	node->m_Pre = head->m_Pre;
	head->m_Pre->m_Next = node;
	head->m_Pre = node;
	list->m_Size++;	//大小增加
}

/*
*  @description : 头部删除元素元素, 要传入函数指针来判断如何删除， 也可使用默认的删除函数
*  @param		: list链表, 处理内部数据的函数
*  @return		: None
*/
void PopFront(List* list)
{
	ASSERTLIST(list);
	if (IsEmpty(list)) {	//为空则不进行操作
		return;
	}
	Node* head = list->m_Head;
	Node* node = head->m_Next;
	node->m_Next->m_Pre = head;	//抽离节点
	head->m_Next = node->m_Next;
	list->deallocate(node->m_Data);	//由 deallocate 函数处理节点内部数据
	free(node);	//释放节点
	node = NULL;
	list->m_Size--;	//大小减小
}

/*
*  @description : 尾删元素元素, 要传入函数指针来判断如何删除， 也可使用默认的删除函数
*  @param		: list链表, deallocate处理内部数据的函数
*  @return		: None
*/
void PopBack(List* list)
{
	ASSERTLIST(list);
	if (IsEmpty(list)) {	//为空则不进行操作
		return;
	}
	Node* head = list->m_Head;
	Node* node = head->m_Pre;
	node->m_Pre->m_Next = head;	//抽离节点
	head->m_Pre = node->m_Pre;
	list->deallocate(node->m_Data);	//由 deallocate 函数处理节点内部数据
	free(node);	//释放节点
	node = NULL;
	list->m_Size--;	//大小减小
}

/*
*  @description : 默认数据释放函数，释放堆区内存
*  @param		: pValue 要释放数据的地址
*  @return		: None
*/
void DefaultDeallocate(void* pValue)
{
	if (pValue) {	//若数据不为空
		free(pValue);	//释放数据
	}
}

/*
*  @description : 在指定节点前插入数据，注意是在其之前
*  @param		: list操作的链表，pos指定的节点，在其前插入数据，pValue要插入的数据
*  @return		: 新加的节点
*/
Node* Insert(List* list, Node* pos, const void* const pValue)
{
	if (!pos || !list || !(list->m_Head)) {
		return NULL;
	}
	Node* node = MALLOC(Node);
	if (!node) {
		return NULL;
	}
	node->m_Data = pValue;
	node->m_Next = pos;
	node->m_Pre = pos->m_Pre;
	pos->m_Pre->m_Next = node;
	pos->m_Pre = node;
	list->m_Size++;
	return node;
}

/*
*  @description : 删除指定节点，并返回其前面的节点,别把头节点传进去了，传进去不会做任何事
*  @param		: list操作的链表，pos指定的节点，deallocate处理内部数据的函数
*  @return		: 删除节点之前的节点
*/
Node* Erase(List* list, Node* pos)
{
	if (!list || !(list->m_Head) || !pos || pos == list->m_Head || IsEmpty(list)) {
		return NULL;
	}
	Node* pre = pos->m_Pre;
	pre->m_Next = pos->m_Next;
	pos->m_Next->m_Pre = pre;
	list->deallocate(pos->m_Data);
	free(pos);
	pos = NULL;
	list->m_Size--;
	return pre;
}

/*
*  @description : 查找某个节点，需要提供查找数据的函数，比较成功时要返回 true
*  @param		: list 操作的链表，findFunc 查找函数，用于定义怎样查找， cmpValue用于比较的值
*  @return		: 查找到的节点，查找失败是返回 NULL
*/
Node* Find(List* list, bool findFunc(void*, void*), void* cmpValue)
{
	if (!list || !list->m_Head || IsEmpty(list)) {
		return NULL;
	}
	for (Node* node = list->m_Head->m_Next; node != list->m_Head; node = node->m_Next) {
		if (findFunc(node->m_Data, cmpValue)) {
			return node;
		}
	}
	return NULL;
}

/*
*  @description : 遍历整个链表，并对节点内的数据执行特定操作，操作由传入的函数决定
*  @param		: list 遍历的链表，operation 操作函数，用于定义怎样处理数据
*  @return		: None
*/
void TraversalOperation(List* list, void operation(void*, void*), void* operateValue)
{
	ASSERTLIST(list);
	for (Node* node = list->m_Head->m_Next; node != list->m_Head; node = node->m_Next) {
		operation(node->m_Data, operateValue);
	}
}

/*
*  @description : 清空链表
*  @param		: list 清空的链表
*  @return		: None
*/
void Clear(List* list)
{
	ASSERTLIST(list);
	while (!IsEmpty(list)) {
		PopBack(list);
	}
}

/*
*  @description : 销毁链表
*  @param		: list 销毁的链表
*  @return		: NULL
*/
List* Destroy(List* list)
{
	if (!list || !list->m_Head) {
		return NULL;
	}
	Clear(list);
	free(list->m_Head);
	free(list);
	list = NULL;
	return list;
}
