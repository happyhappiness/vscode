void sentinelDisconnectCallback(const redisAsyncContext *c, int status) {
    printf("DISCONNECT CALLBACK CALLED: %p (%p)\n", (void*)c, (void*)c->data);
    sentinelDisconnectInstanceFromContext(c);
}