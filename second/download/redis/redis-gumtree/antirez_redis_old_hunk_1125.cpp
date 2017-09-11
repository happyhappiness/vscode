
    snprintf(name,sizeof(name),"sentinel-%.8s-%s",sentinel.myid,type);
    if (redisAsyncCommand(c, sentinelDiscardReplyCallback, ri,
        "CLIENT SETNAME %s", name) == REDIS_OK)
    {
        ri->link->pending_commands++;
    }
