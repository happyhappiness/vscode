void disconnectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
    }
    printf("disconnected...\n");
    aeStop(loop);
}