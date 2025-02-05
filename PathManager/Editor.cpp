/*
 *	Editor.cpp 
 *	
 *	Author: Alejandro Quiroz Carmona
 *	Date: 2024
 *
 */

#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include "PathManager.h"

wchar_t* AppendDirToPathW(wchar_t* path, wchar_t* dir){
	size_t plen = wcslen(path);
	size_t dlen = wcslen(dir);
	size_t rlen = plen + dlen + 2 + 1;

	if(AlreadyInPath(path,dir)){
		return path;
	}

	wchar_t* res = new wchar_t[rlen];

	wcsncpy_s(res, rlen, path, plen);
	wcsncpy_s(res + plen, rlen, L";", 1);
	wcsncpy_s(res + (plen + 1), rlen, dir, dlen);
	wcsncpy_s(res + (plen + 1 + dlen), rlen, L"\0\0", 2);

	return res;
}

wchar_t* RemoveDirFromPathW(wchar_t* path, wchar_t* dir){
	wchar_t* ctx;
	wchar_t* token = wcstok_s(path, L";", &ctx);
	wchar_t* dir_sample = CopyToLowerCase(dir);

	size_t offset = 0;
	size_t tlen;
	wchar_t* res = new wchar_t[BUFFER_SIZE];
	
	while (token){
		if(wcscmp(CopyToLowerCase(token),dir_sample)){
			if(offset){
				wcsncpy_s(res + offset, BUFFER_SIZE, L";", 1);
				offset = offset + 1;
			}

			tlen = wcslen(token);
			wcsncpy_s(res + offset, BUFFER_SIZE, token, tlen);
			offset = offset + tlen;
		}
		token = wcstok_s(NULL, L";", &ctx);
    }

	wcsncpy_s(res + offset, BUFFER_SIZE, L"\0\0", 2);
	delete[] dir_sample;

	return res;
}

int AlreadyInPath(wchar_t* path, wchar_t* dir){
	wchar_t* ctx;
	wchar_t* p = CopyToLowerCase(path);
	wchar_t* d = CopyToLowerCase(dir);
	wchar_t* token = wcstok_s(p, L";", &ctx);
	
	while (token){
		if(!wcscmp(token,d)){
			delete[] p;
			delete[] d;
			return 1;
		}
		token = wcstok_s(NULL, L";", &ctx);
    }

	delete[] p;
	delete[] d;
	return 0;
}

wchar_t* CopyToLowerCase(wchar_t* input){
	size_t len = wcslen(input), offset = len;
	wchar_t* output = new wchar_t[len+1];

	while (len-- > 0){
		*(output++) = towlower(*(input++)); 
	}

	*output = L'\0';

	return output-offset;
}
