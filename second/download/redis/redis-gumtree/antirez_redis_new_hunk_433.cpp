    return RedisModule_ReplyWithSimpleString(ctx,"OK");
}

/* HELLO.ZSUMRANGE key startscore endscore
 * Return the sum of all the scores elements between startscore and endscore. */
int HelloZsumRange_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModuleZsetRange zrange = REDISMODULE_ZSET_RANGE_INIT;
    zrange.type = REDISMODULE_ZSET_RANGE_SCORE;
    if (RedisModule_StringToDouble(argv[2],&zrange.score_start) != REDISMODULE_OK ||
        RedisModule_StringToDouble(argv[3],&zrange.score_end) != REDISMODULE_OK)
    {
        return RedisModule_ReplyWithError(ctx,"ERR invalid range");
    }
    zrange.flags = 0;

    RedisModuleKey *key = RedisModule_OpenKey(ctx,argv[1],
        REDISMODULE_READ|REDISMODULE_WRITE);
    if (RedisModule_KeyType(key) != REDISMODULE_KEYTYPE_ZSET) {
        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
    }

    RedisModule_ZsetFirstInRange(key,&zrange);
    double scoresum = 0;
    while(!RedisModule_ZsetRangeEndReached(key)) {
        double score;
        RedisModuleString *ele = RedisModule_ZsetRangeCurrentElement(key,&score);
        RedisModule_FreeString(ctx,ele);
        scoresum += score;
        RedisModule_ZsetRangeNext(key);
    }
    RedisModule_ZsetRangeStop(key);
    RedisModule_CloseKey(key);
    RedisModule_ReplyWithDouble(ctx,scoresum);
    return REDISMODULE_OK;
}

/* This function must be present on each Redis module. It is used in order to
 * register the commands into the Redis server. */
int RedisModule_OnLoad(RedisModuleCtx *ctx) {
