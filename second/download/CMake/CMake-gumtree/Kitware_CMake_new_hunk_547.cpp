*----------------------------------------------------------------------
*/

#include <windows.h>
#include <stdio.h>
#include <string>
#include <fstream>

/*
+ * Utility func, strstr with size
+ */
const char* StrNStr(const char* start, const char* find, size_t &size) {
