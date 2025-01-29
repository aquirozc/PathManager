#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <wchar.h>
#include <windows.h>
#include "PathManager.h"

#define TASK_APPEND 1;
#define TASK_DELETE 2;

#define SCOPE_LOCAL 1;
#define SCOPE_GLOBAL 2;

int printHelp();
int unimplemented();

int _tmain(int argc, _TCHAR* argv[]){

	if(argc==1){
		return printHelp();
	}

	wchar_t path[BUFFER_SIZE];
	wchar_t pwd[BUFFER_SIZE];
	int task = 0;
	int scope = 0;
	LPWSTR* args = CommandLineToArgvW(GetCommandLineW(), &argc);
	GetCurrentDirectoryW(BUFFER_SIZE, pwd);

	while (--argc > 0) {
	
		wchar_t* arg = toLowerCopy(*(++args));

		if(!wcscmp(arg, L"/add")){

			if(task){
				wprintf(L"ERROR_TO_MANY_ARGS");
				return 4;
			}

			task = TASK_APPEND;

		}else if (!wcscmp(arg, L"/remove")){

			if(task){
				wprintf(L"ERROR_TO_MANY_ARGS");
				return 4;
			}

			task = TASK_DELETE;

		}else if (!wcscmp(arg, L"/user")){

			if(scope){
				wprintf(L"ERROR_TO_MANY_ARGS");
				return 4;
			}

			scope = SCOPE_LOCAL;

		}else if (!wcscmp(arg, L"/system")){

			if(scope){
				wprintf(L"ERROR_TO_MANY_ARGS");
				return 4;
			}

			scope = SCOPE_GLOBAL;

		}else{

			wchar_t* aux = wcschr(arg,':');

			if(!aux){
				wprintf(L"ERROR_BAD_ARGUMENT");
				return 4;
			}

			size_t key_size = aux - arg + 1;
			size_t value_size = wcslen(arg) - key_size + 1;

			wchar_t* key = new wchar_t[key_size];
			wchar_t* value = new wchar_t[value_size];

			wcsncpy_s(key, key_size, arg, key_size-1);
			wcsncpy_s(value, value_size, arg + key_size, value_size - 1);

			if(!wcscmp(key, L"/add-dir")){

				if(task){
					wprintf(L"ERROR_TO_MANY_ARGS");
					return 4;
				}

				task = TASK_APPEND;
				return unimplemented();

			}else if(!wcscmp(key, L"/remove-dir")){

				if(task){
					wprintf(L"ERROR_TO_MANY_ARGS");
					return 4;
				}

				task = TASK_DELETE;
				return unimplemented();
		
			}else{
				wprintf(L"ERROR_BAD_WIDE_ARGUMENT");
				return 4;
			}	
		
		}
	}

	if(!task){
		wprintf(L"ERROR_TASK_NOT_SPECIFIED");
		return 4;
	}

	if(!scope){
		wprintf(L"ERROR_SCOPE_NOT_SPECIFIED");
		return 4;
	}

	if(!(--task)){
		readPath(path,(--scope));
		writePath(appendDirToPath(path,pwd),scope);
	}else{
		readPath(path,(--scope));
		writePath(removeDirFromPath(path,pwd),scope);
	}

	SendMessageTimeoutW(HWND_BROADCAST, WM_SETTINGCHANGE, NULL, NULL, SMTO_ABORTIFHUNG, 20000, NULL);

	return 0;
}

int printHelp(){
	  std::cout << "Path Manager for Windows\n"
              << "Version: Milestone 1\n\n"
              << "PathManager.exe {/Add | /Remove} {/User | /System}\n"
              << "PathManager.exe {/Add-Dir:dir_to_include | /Remove-Dir:dir_to_exclude} \n"
              << "\t\t{/User | /System}\n\n"
              << "DESCRIPTION: \n\n"
              << "\tPath Manager is currently under development.\n\n"
              << "COMMANDS:\n\n"
              << "\t/Add\t\tAppends current directory (aka PWD) to the\n"
              << "\t\t\tend of the path environment variable.\n\n"
              << "\t/Remove\t\tRemoves current directory (aka PWD) from\n"
              << "\t\t\tthe path environment variable.\n\n"
              << "\t/User\t\tTargets local path environment variable.\n\n"
              << "\t/System\t\tTargets global path environment variable.\n\n"
              << "\t/?\t\tDisplay help manual page.\n";

	  return 0;
}

int unimplemented(){
	wprintf(L"ERROR_FLAG_NOT_IMPLEMENTED");
	return 4;
}
