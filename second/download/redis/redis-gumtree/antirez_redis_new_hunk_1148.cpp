    }
}

void _serverAssertPrintObject(robj *o) {
    bugReportStart();
    serverLog(REDIS_WARNING,"=== ASSERTION FAILED OBJECT CONTEXT ===");
    serverLogObjectDebugInfo(o);
}

void _serverAssertWithInfo(client *c, robj *o, char *estr, char *file, int line) {
    if (c) _serverAssertPrintClientInfo(c);
    if (o) _serverAssertPrintObject(o);
    _serverAssert(estr,file,line);
}

void _redisPanic(char *msg, char *file, int line) {
