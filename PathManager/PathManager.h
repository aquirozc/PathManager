#ifndef PATHMANAGER_H
#define PATHMANAGER_H

int readPath(wchar_t* buffer, int isGlobal);
int writePath(wchar_t* buffer, int isGlobal);
wchar_t* appendDirToPath(wchar_t* path, wchar_t* dir)
wchar_t* removeDirFromPath(wchar_t* path, wchar_t* dir)

#endif
