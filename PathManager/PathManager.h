#ifndef PATHMANAGER_H
#define PATHMANAGER_H
#define BUFFER_SIZE 16383

int ReadPathValueW(wchar_t* buffer, int isGlobal);
int WritePathValueW(wchar_t* buffer, int isGlobal);
wchar_t* AppendDirToPathW(wchar_t* path, wchar_t* dir);
wchar_t* RemoveDirFromPathW(wchar_t* path, wchar_t* dir);
int AlreadyInPath(wchar_t* path, wchar_t* dir);
wchar_t* CopyToLowerCase(wchar_t * input);
int GetDirFullPathW(wchar_t* fname, wchar_t* dest);

#endif
