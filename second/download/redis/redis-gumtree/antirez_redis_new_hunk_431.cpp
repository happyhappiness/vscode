 * the initial error code. The function only provides the initial "-", so
 * the usage is, for example:
 *
 *  RM_ReplyWithError(ctx,"ERR Wrong Type");
 *
 * and not just:
 *
 *  RM_ReplyWithError(ctx,"Wrong Type");
 *
 * The function always returns REDISMODULE_OK.
 */
int RM_ReplyWithError(RedisModuleCtx *ctx, const char *err) {
    return replyWithStatus(ctx,err,"-");
}

/* Reply with a simple string (+... \r\n in RESP protocol). This replies
 * are suitable only when sending a small non-binary string with small
 * overhead, like "OK" or similar replies.
 *
 * The function always returns REDISMODULE_OK. */
int RM_ReplyWithSimpleString(RedisModuleCtx *ctx, const char *msg) {
    return replyWithStatus(ctx,msg,"+");
}

/* Reply with an array type of 'len' elements. However 'len' other calls
 * to ReplyWith* style functions must follow in order to emit the elements
 * of the array.
 *
 * The function always returns REDISMODULE_OK. */
int RM_ReplyWithArray(RedisModuleCtx *ctx, int len) {
    addReplyMultiBulkLen(ctx->client,len);
    return REDISMODULE_OK;
}

/* Reply with a bulk string, taking in input a C buffer pointer and length.
 *
 * The function always returns REDISMODULE_OK. */
int RM_ReplyWithStringBuffer(RedisModuleCtx *ctx, const char *buf, size_t len) {
    addReplyBulkCBuffer(ctx->client,(char*)buf,len);
    return REDISMODULE_OK;
}

/* Reply with a bulk string, taking in input a RedisModuleString object.
 *
 * The function always returns REDISMODULE_OK. */
int RM_ReplyWithString(RedisModuleCtx *ctx, RedisModuleString *str) {
    addReplyBulk(ctx->client,str);
    return REDISMODULE_OK;
}

/* Reply to the client with a NULL. In the RESP protocol a NULL is encoded
 * as the string "$-1\r\n".
 *
 * The function always returns REDISMODULE_OK. */
int RM_ReplyWithNull(RedisModuleCtx *ctx) {
    addReply(ctx->client,shared.nullbulk);
    return REDISMODULE_OK;
}

/* Reply exactly what a Redis command returned us with RedisModule_Call().
 * This function is useful when we use RedisModule_Call() in order to
 * execute some command, as we want to reply to the client exactly the
 * same reply we obtained by the command.
 *
 * The function always returns REDISMODULE_OK. */
int RM_ReplyWithCallReply(RedisModuleCtx *ctx, RedisModuleCallReply *reply) {
    sds proto = sdsnewlen(reply->proto, reply->protolen);
    addReplySds(ctx->client,proto);
    return REDISMODULE_OK;
}

/* Send a string reply obtained converting the double 'd' into a bulk string.
 * This function is basically equivalent to converting a double into
 * a string into a C buffer, and then calling the function
 * RedisModule_ReplyWithStringBuffer() with the buffer and length.
 *
 * The function always returns REDISMODULE_OK. */
int RM_ReplyWithDouble(RedisModuleCtx *ctx, double d) {
    addReplyDouble(ctx->client,d);
    return REDISMODULE_OK;
