}

void sentinelDisconnectCallback(const redisAsyncContext *c, int status) {
    REDIS_NOTUSED(status);
    instanceLinkConnectionError(c);
}

