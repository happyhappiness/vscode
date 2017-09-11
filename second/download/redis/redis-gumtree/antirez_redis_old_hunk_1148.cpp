    }
}

void _redisAssertPrintObject(robj *o) {
    bugReportStart();
    serverLog(REDIS_WARNING,"=== ASSERTION FAILED OBJECT CONTEXT ===");
    serverLogObjectDebugInfo(o);
}

void _redisAssertWithInfo(client *c, robj *o, char *estr, char *file, int line) {
    if (c) _redisAssertPrintClientInfo(c);
    if (o) _redisAssertPrintObject(o);
    _redisAssert(estr,file,line);
}

void _redisPanic(char *msg, char *file, int line) {
