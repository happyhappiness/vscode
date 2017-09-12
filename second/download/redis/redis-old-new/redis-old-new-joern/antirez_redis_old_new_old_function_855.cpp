void bugReportStart(void) {
    if (server.bug_report_start == 0) {
        serverLog(REDIS_WARNING,
            "\n\n=== REDIS BUG REPORT START: Cut & paste starting from here ===");
        server.bug_report_start = 1;
    }
}