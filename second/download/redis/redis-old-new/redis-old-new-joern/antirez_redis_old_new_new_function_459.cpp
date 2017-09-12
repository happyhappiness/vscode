int HelloHCopy_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModule_AutoMemory(ctx); /* Use automatic memory management. */

    if (argc != 4) return RedisModule_WrongArity(ctx);
    RedisModuleKey *key = RedisModule_OpenKey(ctx,argv[1],
        REDISMODULE_READ|REDISMODULE_WRITE);
    int type = RedisModule_KeyType(key);
    if (type != REDISMODULE_KEYTYPE_HASH &&
        type != REDISMODULE_KEYTYPE_EMPTY)
    {
        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
    }

    /* XXX modify me. */
    RedisModule_HashSet(key,REDISMODULE_HSET_NONE,argv[2],argv[3],NULL);
    RedisModule_HashSet(key,REDISMODULE_HSET_CFIELDS,"foo",argv[3],NULL);
    RedisModule_ReplyWithLongLong(ctx,0);
    return REDISMODULE_OK;
}