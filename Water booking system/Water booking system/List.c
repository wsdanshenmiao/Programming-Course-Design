#include "List.h"

#define MALLOC(T) ((T*)malloc(sizeof(T)))
#define ASSERTLIST(T) if ((!(T)) || (!((T)->m_Head))) {return;}
#define ASSERTNODE(T) if (!(T)) {return;}

//Public

/*
*  @description : �ж������Ƿ�Ϊ��
*  @param		: listΪ����
*  @return		: Ϊ��ʱ����true
*/
bool IsEmpty(const List* const list)
{
	return list->m_Size == 0 && list->m_Head->m_Next == list->m_Head;
}

/*
*  @description : ��ʼ������
*  @param		: None
*  @return		: ָ�������ָ��
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
	head->m_Data = NULL;	//��ʼ��ͷ�ڵ�
	head->m_Next = head;
	head->m_Pre = head;
	list->m_Head = head;	//��ʼ������
	list->m_Size = 0;
	list->deallocate = deallocate;
	return list;
}

/*
*  @description : ͷ�˲���Ԫ�أ������Ѿ�������ڴ������
*  @param		: list����, pValue���ݵĵ�ַ
*  @return		: None
*/
void PushFront(List* list, const void* const pValue)
{
	ASSERTLIST(list);
	Node* head = list->m_Head;
	Node* node = MALLOC(Node);
	ASSERTNODE(node);
	node->m_Data = pValue;	//�ӹ�����
	node->m_Pre = head;	//����ڵ�
	node->m_Next = head->m_Next;
	head->m_Next->m_Pre = node;
	head->m_Next = node;
	list->m_Size++;	//��������
}

/*
*  @description : β������Ԫ�أ������Ѿ�������ڴ������
*  @param		: list����, pValue���ݵĵ�ַ
*  @return		: None
*/
void PushBack(List* list, const void* const pValue)
{
	ASSERTLIST(list);
	Node* head = list->m_Head;
	Node* node = MALLOC(Node);
	ASSERTNODE(node);
	node->m_Data = pValue;	//�ӹ�����
	node->m_Next = head;	//����ڵ�
	node->m_Pre = head->m_Pre;
	head->m_Pre->m_Next = node;
	head->m_Pre = node;
	list->m_Size++;	//��С����
}

/*
*  @description : ͷ��ɾ��Ԫ��Ԫ��, Ҫ���뺯��ָ�����ж����ɾ���� Ҳ��ʹ��Ĭ�ϵ�ɾ������
*  @param		: list����, �����ڲ����ݵĺ���
*  @return		: None
*/
void PopFront(List* list)
{
	ASSERTLIST(list);
	if (IsEmpty(list)) {	//Ϊ���򲻽��в���
		return;
	}
	Node* head = list->m_Head;
	Node* node = head->m_Next;
	node->m_Next->m_Pre = head;	//����ڵ�
	head->m_Next = node->m_Next;
	list->deallocate(node->m_Data);	//�� deallocate ��������ڵ��ڲ�����
	free(node);	//�ͷŽڵ�
	node = NULL;
	list->m_Size--;	//��С��С
}

/*
*  @description : βɾԪ��Ԫ��, Ҫ���뺯��ָ�����ж����ɾ���� Ҳ��ʹ��Ĭ�ϵ�ɾ������
*  @param		: list����, deallocate�����ڲ����ݵĺ���
*  @return		: None
*/
void PopBack(List* list)
{
	ASSERTLIST(list);
	if (IsEmpty(list)) {	//Ϊ���򲻽��в���
		return;
	}
	Node* head = list->m_Head;
	Node* node = head->m_Pre;
	node->m_Pre->m_Next = head;	//����ڵ�
	head->m_Pre = node->m_Pre;
	list->deallocate(node->m_Data);	//�� deallocate ��������ڵ��ڲ�����
	free(node);	//�ͷŽڵ�
	node = NULL;
	list->m_Size--;	//��С��С
}

/*
*  @description : Ĭ�������ͷź������ͷŶ����ڴ�
*  @param		: pValue Ҫ�ͷ����ݵĵ�ַ
*  @return		: None
*/
void DefaultDeallocate(void* pValue)
{
	if (pValue) {	//�����ݲ�Ϊ��
		free(pValue);	//�ͷ�����
	}
}

/*
*  @description : ��ָ���ڵ�ǰ�������ݣ�ע��������֮ǰ
*  @param		: list����������posָ���Ľڵ㣬����ǰ�������ݣ�pValueҪ���������
*  @return		: �¼ӵĽڵ�
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
*  @description : ɾ��ָ���ڵ㣬��������ǰ��Ľڵ�,���ͷ�ڵ㴫��ȥ�ˣ�����ȥ�������κ���
*  @param		: list����������posָ���Ľڵ㣬deallocate�����ڲ����ݵĺ���
*  @return		: ɾ���ڵ�֮ǰ�Ľڵ�
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
*  @description : ����ĳ���ڵ㣬��Ҫ�ṩ�������ݵĺ������Ƚϳɹ�ʱҪ���� true
*  @param		: list ����������findFunc ���Һ��������ڶ����������ң� cmpValue���ڱȽϵ�ֵ
*  @return		: ���ҵ��Ľڵ㣬����ʧ���Ƿ��� NULL
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
*  @description : ���������������Խڵ��ڵ�����ִ���ض������������ɴ���ĺ�������
*  @param		: list ����������operation �������������ڶ���������������
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
*  @description : �������
*  @param		: list ��յ�����
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
*  @description : ��������
*  @param		: list ���ٵ�����
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
