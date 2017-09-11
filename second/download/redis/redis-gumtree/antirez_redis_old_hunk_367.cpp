
/* =========================== Crash handling  ============================== */

void _serverAssert(char *estr, char *file, int line) {
    bugReportStart();
    serverLog(LL_WARNING,"=== ASSERTION FAILED ===");
    serverLog(LL_WARNING,"==> %s:%d '%s' is not true",file,line,estr);
