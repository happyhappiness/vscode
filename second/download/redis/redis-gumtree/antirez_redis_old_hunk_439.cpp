
/* Send an integer reply with the specified long long value.
 * The function always returns REDISMODULE_OK. */
int RedisModule_ReplyWithLongLong(RedisModuleCtx *ctx, long long ll) {
    addReplyLongLong(ctx->client,ll);
    return REDISMODULE_OK;
}

/* Reply with an error or simple string (status message). Used to implement
 * ReplyWithSimpleString() and ReplyWithError(). */
int RedisModule_ReplyWithStatus(RedisModuleCtx *ctx, const char *msg, char *prefix) {
    sds strmsg = sdsnewlen(prefix,1);
    strmsg = sdscat(strmsg,msg);
    strmsg = sdscatlen(strmsg,"\r\n",2);
