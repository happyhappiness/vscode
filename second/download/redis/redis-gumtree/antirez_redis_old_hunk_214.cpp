    targ[1] = (void*)(unsigned long) delay;

    if (pthread_create(&tid,NULL,HelloBlock_ThreadMain,targ) != 0) {
        /* RedisModule_BlockedClientAbort(bc); */
        return RedisModule_ReplyWithError(ctx,"-ERR Can't start thread");
    }
    return REDISMODULE_OK;
