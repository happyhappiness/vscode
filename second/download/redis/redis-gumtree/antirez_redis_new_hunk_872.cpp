    _serverAssert(estr,file,line);
}

void _serverPanic(char *msg, char *file, int line) {
    bugReportStart();
    serverLog(LL_WARNING,"------------------------------------------------");
    serverLog(LL_WARNING,"!!! Software Failure. Press left mouse button to continue");
    serverLog(LL_WARNING,"Guru Meditation: %s #%s:%d",msg,file,line);
#ifdef HAVE_BACKTRACE
    serverLog(LL_WARNING,"(forcing SIGSEGV in order to print the stack trace)");
#endif
    serverLog(LL_WARNING,"------------------------------------------------");
    *((char*)-1) = 'x';
}

void bugReportStart(void) {
    if (server.bug_report_start == 0) {
        serverLog(LL_WARNING,
            "\n\n=== REDIS BUG REPORT START: Cut & paste starting from here ===");
        server.bug_report_start = 1;
    }
