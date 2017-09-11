
void _redisPanic(char *msg, char *file, int line) {
    bugReportStart();
    redisLog(REDIS_WARNING,"------------------------------------------------");
    redisLog(REDIS_WARNING,"!!! Software Failure. Press left mouse button to continue");
    redisLog(REDIS_WARNING,"Guru Meditation: %s #%s:%d",msg,file,line);
#ifdef HAVE_BACKTRACE
    redisLog(REDIS_WARNING,"(forcing SIGSEGV in order to print the stack trace)");
#endif
    redisLog(REDIS_WARNING,"------------------------------------------------");
    *((char*)-1) = 'x';
}

void bugReportStart(void) {
    if (server.bug_report_start == 0) {
        redisLog(REDIS_WARNING,
            "\n\n=== REDIS BUG REPORT START: Cut & paste starting from here ===");
        server.bug_report_start = 1;
    }
