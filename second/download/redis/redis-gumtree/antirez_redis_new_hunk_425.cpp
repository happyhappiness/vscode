        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
    }

    if (RedisModule_ZsetFirstInLexRange(key,argv[2],argv[3]) != REDISMODULE_OK) {
        return RedisModule_ReplyWithError(ctx,"invalid range");
    }

    int arraylen = 0;
    RedisModule_ReplyWithArray(ctx,REDISMODULE_POSTPONED_ARRAY_LEN);
    while(!RedisModule_ZsetRangeEndReached(key)) {
        double score;
        RedisModuleString *ele = RedisModule_ZsetRangeCurrentElement(key,&score);
