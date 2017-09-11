 * the initial error code. The function only provides the initial "-", so
 * the usage is, for example:
 *
 * RedisModule_ReplyWithError(ctx,"ERR Wrong Type");
 *
 * and not just:
 *
 * RedisModule_ReplyWithError(ctx,"Wrong Type");
 */
int RedisModule_ReplyWithError(RedisModuleCtx *ctx, const char *err) {
    return RedisModule_ReplyWithStatus(ctx,err,"-");
}

/* Reply with a simple string (+... \r\n in RESP protocol). This replies
 * are suitalbe only when sending a small non-binary string wiht small
 * overhead, like "OK" or similar replies. */
int RedisModule_ReplyWithSimpleString(RedisModuleCtx *ctx, const char *msg) {
    return RedisModule_ReplyWithStatus(ctx,msg,"+");
}

/* Reply with an array type of 'len' elements. However 'len' other calls
 * to ReplyWith* style functions must follow in order to emit the elements
 * of the array. */
int RedisModule_ReplyWithArray(RedisModuleCtx *ctx, int len) {
    addReplyMultiBulkLen(ctx->client,len);
    return REDISMODULE_OK;
}

/* Reply with a bulk string, taking in input a C buffer pointer and length. */
int RedisModule_ReplyWithStringBuffer(RedisModuleCtx *ctx, const char *buf, size_t len) {
    addReplyBulkCBuffer(ctx->client,(char*)buf,len);
    return REDISMODULE_OK;
}

/* Reply with a bulk string, taking in input a RedisModuleString object. */
int RedisModule_ReplyWithString(RedisModuleCtx *ctx, RedisModuleString *str) {
    addReplyBulk(ctx->client,str);
    return REDISMODULE_OK;
}
