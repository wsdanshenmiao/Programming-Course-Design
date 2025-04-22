#ifndef __LOGINSYSTEM__H__
#define __LOGINSYSTEM__H__

#include <string.h>
#include <errno.h>
#include <io.h>
#include "GlobalVariable.h"
#include "List.h"
#include "Util.h"


Node* UserLoginUI();

Userinfo* NewUser(Userinfo e);
void UserRegister();
bool FindUser(void* pValue, void* cmpValue);

bool MerchantLogin(char correctPassword[20]);	//商家登录
Node* UserLogin();	//用户登录
void ChangePassword(char** correctPassword);

#endif // !__LOGINSYSTEM__H__

