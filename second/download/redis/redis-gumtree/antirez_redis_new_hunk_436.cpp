    }

    long long count;
    if ((RedisModule_StringToLongLong(argv[3],&count) != REDISMODULE_OK) ||
        (count < 0))
    {
        return RedisModule_ReplyWithError(ctx,"ERR invalid count");
    }

    while(count-- > 0) {
        RedisModuleString *ele;
