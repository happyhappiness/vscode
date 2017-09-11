 *
 * The string is created by copying the `len` bytes starting
 * at `ptr`. No reference is retained to the passed buffer. */
RedisModuleString *RM_CreateString(RedisModuleCtx *ctx, const char *ptr, size_t len) {
    RedisModuleString *o = createStringObject(ptr,len);
    autoMemoryAdd(ctx,REDISMODULE_AM_STRING,o);
    return o;
}


/* Create a new module string object from a printf format and arguments. 
 * The returned string must be freed with RedisModule_FreeString(), unless automatic 
 * memory is enabled.
 *
 * The string is created using the sds formatter function sdscatvprintf() */ 
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


/* Like RedisModule_CreatString(), but creates a string starting from a long long
 * integer instead of taking a buffer and its length.
 *
