
void _redisAssert(char *estr, char *file, int line) {
    bugReportStart();
    serverLog(REDIS_WARNING,"=== ASSERTION FAILED ===");
    serverLog(REDIS_WARNING,"==> %s:%d '%s' is not true",file,line,estr);
#ifdef HAVE_BACKTRACE
    server.assert_failed = estr;
    server.assert_file = file;
    server.assert_line = line;
    serverLog(REDIS_WARNING,"(forcing SIGSEGV to print the bug report.)");
#endif
    *((char*)-1) = 'x';
}
