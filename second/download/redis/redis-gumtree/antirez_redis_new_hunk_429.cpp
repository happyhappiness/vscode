 * another time backward. The two scores, returned as a two element array,
 * should match.*/
int HelloZsumRange_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    double score_start, score_end;

    if (RedisModule_StringToDouble(argv[2],&score_start) != REDISMODULE_OK ||
        RedisModule_StringToDouble(argv[3],&score_end) != REDISMODULE_OK)
    {
        return RedisModule_ReplyWithError(ctx,"ERR invalid range");
    }

    RedisModuleKey *key = RedisModule_OpenKey(ctx,argv[1],
        REDISMODULE_READ|REDISMODULE_WRITE);
