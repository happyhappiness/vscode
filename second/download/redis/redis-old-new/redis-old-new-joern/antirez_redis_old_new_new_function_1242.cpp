void sentinelSetClientName(sentinelRedisInstance *ri, redisAsyncContext *c, char *type) {
    char name[64];

    snprintf(name,sizeof(name),"sentinel-%.8s-%s",sentinel.myid,type);
    if (redisAsyncCommand(c, sentinelDiscardReplyCallback, NULL,
        "CLIENT SETNAME %s", name) == REDIS_OK)
    {
        ri->pending_commands++;
    }
}