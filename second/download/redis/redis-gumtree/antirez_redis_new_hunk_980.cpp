}

void sentinelDisconnectCallback(const redisAsyncContext *c, int status) {
    UNUSED(status);
    instanceLinkConnectionError(c);
}

