
void _redisPanic(char *msg, char *file, int line) {
    bugReportStart();
    serverLog(REDIS_WARNING,"------------------------------------------------");
    serverLog(REDIS_WARNING,"!!! Software Failure. Press left mouse button to continue");
    serverLog(REDIS_WARNING,"Guru Meditation: %s #%s:%d",msg,file,line);
#ifdef HAVE_BACKTRACE
    serverLog(REDIS_WARNING,"(forcing SIGSEGV in order to print the stack trace)");
#endif
    serverLog(REDIS_WARNING,"------------------------------------------------");
    *((char*)-1) = 'x';
}

void bugReportStart(void) {
    if (server.bug_report_start == 0) {
        serverLog(REDIS_WARNING,
            "\n\n=== REDIS BUG REPORT START: Cut & paste starting from here ===");
        server.bug_report_start = 1;
    }
