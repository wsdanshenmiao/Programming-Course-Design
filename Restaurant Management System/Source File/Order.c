#include "Order.h"

void* CreateOrderInfoData()
{
	OrderInfo* order = MALLOC(OrderInfo);
	if (NULL == order)return NULL;

	return order;
}

int CmpOrderInfoByClient(void* order0, void* order1)
{
	assert(ASSERTPOINTER(order0) && ASSERTPOINTER(order1));
	ClientInfo* c0 = ((OrderInfo*)order0)->m_Client;
	ClientInfo* c1 = ((OrderInfo*)order1)->m_Client;

	if (c0 == c1)return 0;
	else return 1;
}

