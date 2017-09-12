RedisModuleString *RM_CreateStringPrintf(RedisModuleCtx *ctx, const char *fmt, ...) {
    sds s = sdsempty();

    va_list ap;
    va_start(ap, fmt);
    s = sdscatvprintf(s, fmt, ap);
    va_end(ap);

    RedisModuleString *o = createObject(OBJ_STRING, s);
    autoMemoryAdd(ctx,REDISMODULE_AM_STRING,o);

    return o;
}