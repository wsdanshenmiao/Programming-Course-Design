#ifndef __LOGINSYSTEM__H__
#define __LOGINSYSTEM__H__

#include <string.h>
#include <errno.h>
#include <io.h>
#include "GlobalVariable.h"
#include "List.h"


Node* UserLoginUI();

void PrintUser(void* pValue);
Userinfo* NewUser(Userinfo e);
void UserRegister();
bool FindUser(void* pValue, void* cmpValue);
void SaveUserinfo(void* pValue, void* operateValue);

bool MerchantLogin();	//商家登录
Node* UserLogin();	//用户登录

#endif // !__LOGINSYSTEM__H__

