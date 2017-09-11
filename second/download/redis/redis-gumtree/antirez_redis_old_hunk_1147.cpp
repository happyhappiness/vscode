
/* =========================== Crash handling  ============================== */

void _redisAssert(char *estr, char *file, int line) {
    bugReportStart();
    serverLog(REDIS_WARNING,"=== ASSERTION FAILED ===");
    serverLog(REDIS_WARNING,"==> %s:%d '%s' is not true",file,line,estr);
