void _serverAssertPrintObject(robj *o) {
    bugReportStart();
    serverLog(REDIS_WARNING,"=== ASSERTION FAILED OBJECT CONTEXT ===");
    serverLogObjectDebugInfo(o);
}