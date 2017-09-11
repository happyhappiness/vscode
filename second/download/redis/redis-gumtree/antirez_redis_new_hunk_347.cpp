#include <sys/stat.h>
#include <sys/param.h>

#define rdbExitReportCorruptRDB(reason) rdbCheckThenExit(reason, __LINE__);

void rdbCheckThenExit(char *reason, int where) {
