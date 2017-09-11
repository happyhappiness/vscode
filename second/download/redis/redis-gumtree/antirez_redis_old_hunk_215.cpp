}


/* Create a new module string object from a printf format and arguments. 
 * The returned string must be freed with RedisModule_FreeString(), unless automatic 
 * memory is enabled.
 *
 * The string is created using the sds formatter function sdscatvprintf() */ 
RedisModuleString *RM_CreateStringPrintf(RedisModuleCtx *ctx, const char *fmt, ...) {
    sds s = sdsempty();

