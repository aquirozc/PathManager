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

wchar_t* appendDirToPath(wchar_t* path, wchar_t* dir){
	
	size_t plen = wcslen(path);
	size_t dlen = wcslen(dir);
	size_t rlen = plen + dlen + 2 + 1;

	wchar_t* res = new wchar_t[rlen];

	wcsncpy_s(res, rlen, path, plen);
	wcsncpy_s(res + plen, rlen, L";", 1);
	wcsncpy_s(res + (plen + 1), rlen, dir, dlen);
	wcsncpy_s(res + (plen + 1 + dlen), rlen, L"\0\0", 2);

	return res;

}

wchar_t* removeDirFromPath(wchar_t* path, wchar_t* dir){

	wchar_t* ctx;
	wchar_t* token = wcstok_s(path, L";", &ctx);

	size_t offset = 0;
	size_t tlen;
	wchar_t* res = new wchar_t[BUFFER_SIZE];
	
	while (token){

		if(wcscmp(token,dir)){
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

	return res;

}

wchar_t* toLowerCopy(wchar_t * input){
	size_t len = wcslen(input);
	size_t offset = len;
	wchar_t* output = new wchar_t[len+1];

	while (len-- > 0){
		*(output++) = towlower(*(input++)); 
	}

	*output = L'\0';

	return output-offset;
}
