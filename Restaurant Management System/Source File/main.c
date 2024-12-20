#include "ManagementAPP.h"

int main()
{
	ManagementAPP* app = MALLOC(ManagementAPP);
	int errorInfo = 0;
	if (NULL == app) {
		return -1;
	}
	if (InitManagementAPP(app)) {
		errorInfo = 0 == RunManagementAPP(app) ? 0 : -1;
		ExitManagementAPP(app);
	}
	else {
		errorInfo = -1;
	}
	free(app);
	app = NULL;
	return errorInfo;
}

