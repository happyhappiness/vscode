    }

    long long count;
    if ((RedisModule_StringToLongLong(argv[3],&count) != REDISMODULE_OK) ||
        (count < 0)) {
        RedisModule_CloseKey(srckey);
        RedisModule_CloseKey(dstkey);
        return RedisModule_ReplyWithError(ctx,"ERR invalid count");
