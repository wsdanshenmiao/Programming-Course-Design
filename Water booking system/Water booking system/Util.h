#ifndef __UTIL__H__
#define __UTIL__H__

#include <string.h>
//´æ·Å¸¨Öúº¯Êı

inline void CleanBuffer()
{
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}

// ×Ö·û´®ÊäÈë¼ì²â£¬ÊäÈëÊ§°Ü·µ»Øtrue
inline bool StrInputFailure(int erromes, char* name, size_t size)
{
	if (!name) {
		return true;
	}
	size_t len = strnlen(name, size);
	if (!erromes || erromes == EOF || len == 0 || len >= size) {
		return true;
	}
	return false;
}

// Êı×ÖÊäÈë¼ì²â£¬ÊäÈëÊ§°Ü·µ»Øtrue
inline bool NumInputFailure(int erromes)
{
	if (!erromes || erromes == EOF) {
		return true;
	}
	return false;
}


#endif // !__HELLPFUNC__H__

