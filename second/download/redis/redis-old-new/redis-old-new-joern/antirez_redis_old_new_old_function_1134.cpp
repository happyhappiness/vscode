void sentinelLinkEstablishedCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) instanceLinkConnectionError(c);
}