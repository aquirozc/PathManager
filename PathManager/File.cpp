/*
 *	File.cpp 
 *	
 *	Author: Alejandro Quiroz Carmona
 *	Date: 2025
 *
 */

#include <wchar.h>
#include <windows.h>
#include "PathManager.h"

int GetDirFullPathW(wchar_t* fname, wchar_t* dest){

	GetFullPathNameW(fname,BUFFER_SIZE,dest,NULL);
	DWORD attr = GetFileAttributesW(dest);

	if(attr == INVALID_FILE_ATTRIBUTES){
		wprintf(L"Error: Failed to read file attributes");
		return 0;
	}

	return attr & FILE_ATTRIBUTE_DIRECTORY;
	
}