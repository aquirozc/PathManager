/*
 *	Environment.cpp 
 *
 *	Provides read and write access to 
 *	Windows PATH environmental variables
 *	by manipulating the corresponding
 *	registry keys using the Win32 API
 *	
 *	Author: Alejandro Quiroz Carmona
 *	Date: 2024
 *
 */

#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include <winreg.h>
#include "PathManager.h"

#define GLOBAL_HKEY HKEY_LOCAL_MACHINE
#define GLOBAL_SUBKEY L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment"
#define GLOBAL_TYPE REG_EXPAND_SZ

#define LOCAL_HKEY HKEY_CURRENT_USER
#define LOCAL_SUBKEY L"Environment"
#define LOCAL_TYPE REG_SZ

int ReadPathValueW(wchar_t* buffer, int isGlobal) {
    int error = 0;

	DWORD size = BUFFER_SIZE;
    HKEY hkey = LOCAL_HKEY;
    LPCWSTR skey = LOCAL_SUBKEY;
    HKEY hkResult;

    if (isGlobal) {
        hkey = GLOBAL_HKEY;
        skey = GLOBAL_SUBKEY;
    }

    if (RegCreateKeyExW(hkey, skey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ, NULL, &hkResult, NULL) == ERROR_SUCCESS) {

		if (RegQueryValueExW(hkResult, L"Path", NULL, NULL, (LPBYTE)buffer, &size) != ERROR_SUCCESS){
			printf("Error : Couldn't read the specified registry key\n");
			error = 4;
		}

    } else {
        printf("Error : Couldn't load the specified registry key\n");
        error = 4;
    }

	RegCloseKey(hkResult);
    return error;
}

int WritePathValueW(wchar_t* buffer, int isGlobal) {
    int error = 0;

	DWORD size = (wcslen(buffer) * 2) + 4;
    HKEY hkey = LOCAL_HKEY;
    LPCWSTR skey = LOCAL_SUBKEY;
	DWORD rtype = LOCAL_TYPE;
    HKEY hkResult;

    if (isGlobal) {
        hkey = GLOBAL_HKEY;
        skey = GLOBAL_SUBKEY;
		rtype = GLOBAL_TYPE;
    }

    if (RegCreateKeyExW(hkey, skey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hkResult, NULL) == ERROR_SUCCESS) {

		if (RegSetKeyValueW(hkResult,NULL,L"Path", rtype, buffer, size)!= ERROR_SUCCESS){
			printf("Error : Couldn't write the specified registry key\n");
			error = 4;
		}

    } else {
		printf("Error : Couldn't load the specified registry key\n");
        error = 4;
    }

	RegCloseKey(hkResult);
    return error;
}