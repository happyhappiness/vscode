void sentinelDisconnectCallback(const redisAsyncContext *c, int status) {
    sentinelDisconnectInstanceFromContext(c);
}