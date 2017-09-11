/* Hiredis connection established / disconnected callbacks. We need them
 * just to cleanup our link state. */
void sentinelLinkEstablishedCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) instanceLinkConnectionError(c);
}

void sentinelDisconnectCallback(const redisAsyncContext *c, int status) {
