#include <stdio.h>
#include <tchar.h>
#include <wchar.h>
#include "PathManager.h"

#define BUFFER_SIZE 16383

int _tmain(int argc, _TCHAR* argv[]){
	wchar_t local_path[BUFFER_SIZE];
	wchar_t global_path[BUFFER_SIZE];

	readPath(local_path, 0);
	readPath(global_path, 1);

	wprintf(L"Local Path: %s\n\n", local_path);
	wprintf(L"Global Path: %s", global_path);

	while(1);

	return 0;
}

