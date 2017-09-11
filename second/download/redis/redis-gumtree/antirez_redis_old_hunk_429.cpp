 * another time backward. The two scores, returned as a two element array,
 * should match.*/
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
