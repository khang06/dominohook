#pragma once
#include <Windows.h>

/************************************************
	CLASS NAME:
		Quick Patch
	AUTHOR:
		CPunch
	DESCRIPTION:
		Custom hot-patching API for windows operating system. Made for GIDFO for bypassing some slow memcheck operations.
*************************************************/

#define PATCH_SIZE 6

class QPatch
{
private:
	void * addr;
	DWORD oldproc;
	BYTE* orig_bytes;
	BYTE* new_bytes;
	size_t size;
public:
	QPatch(void * ad, BYTE* n_bytes, size_t sz);
	bool patch();
	bool unpatch();
};
