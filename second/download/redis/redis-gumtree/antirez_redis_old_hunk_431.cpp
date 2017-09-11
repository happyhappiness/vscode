 * the initial error code. The function only provides the initial "-", so
 * the usage is, for example:
 *
 * RM_ReplyWithError(ctx,"ERR Wrong Type");
 *
 * and not just:
 *
 * RM_ReplyWithError(ctx,"Wrong Type");
 */
int RM_ReplyWithError(RedisModuleCtx *ctx, const char *err) {
    return RM_ReplyWithStatus(ctx,err,"-");
}

/* Reply with a simple string (+... \r\n in RESP protocol). This replies
 * are suitalbe only when sending a small non-binary string wiht small
 * overhead, like "OK" or similar replies. */
int RM_ReplyWithSimpleString(RedisModuleCtx *ctx, const char *msg) {
    return RM_ReplyWithStatus(ctx,msg,"+");
}

/* Reply with an array type of 'len' elements. However 'len' other calls
 * to ReplyWith* style functions must follow in order to emit the elements
 * of the array. */
int RM_ReplyWithArray(RedisModuleCtx *ctx, int len) {
    addReplyMultiBulkLen(ctx->client,len);
    return REDISMODULE_OK;
}

/* Reply with a bulk string, taking in input a C buffer pointer and length. */
int RM_ReplyWithStringBuffer(RedisModuleCtx *ctx, const char *buf, size_t len) {
    addReplyBulkCBuffer(ctx->client,(char*)buf,len);
    return REDISMODULE_OK;
}

/* Reply with a bulk string, taking in input a RedisModuleString object. */
int RM_ReplyWithString(RedisModuleCtx *ctx, RedisModuleString *str) {
    addReplyBulk(ctx->client,str);
    return REDISMODULE_OK;
}

/* Reply with NULL. */
int RM_ReplyWithNull(RedisModuleCtx *ctx) {
    addReply(ctx->client,shared.nullbulk);
    return REDISMODULE_OK;
}

/* Reply exactly what a Redis command returned us with RM_Call(). */
int RM_ReplyWithCallReply(RedisModuleCtx *ctx, RedisModuleCallReply *reply) {
    sds proto = sdsnewlen(reply->proto, reply->protolen);
    addReplySds(ctx->client,proto);
    return REDISMODULE_OK;
}

/* Send a string reply obtained converting the double 'd' into a string. */
int RM_ReplyWithDouble(RedisModuleCtx *ctx, double d) {
    addReplyDouble(ctx->client,d);
    return REDISMODULE_OK;
