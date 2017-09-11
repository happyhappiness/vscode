 *
 * The string is created by copying the `len` bytes starting
 * at `ptr`. No reference is retained to the passed buffer. */
RedisModuleString *RM_CreateString(RedisModuleCtx *ctx, const char *ptr, size_t len)
{
    RedisModuleString *o = createStringObject(ptr,len);
    autoMemoryAdd(ctx,REDISMODULE_AM_STRING,o);
    return o;
}

/* Like RedisModule_CreatString(), but creates a string starting from a long long
 * integer instead of taking a buffer and its length.
 *
