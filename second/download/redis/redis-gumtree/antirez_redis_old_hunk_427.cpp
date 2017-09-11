 * to ReplyWith* style functions must follow in order to emit the elements
 * of the array.
 *
 * The function always returns REDISMODULE_OK. */
int RM_ReplyWithArray(RedisModuleCtx *ctx, long len) {
    addReplyMultiBulkLen(ctx->client,len);
    return REDISMODULE_OK;
}

/* Reply with a bulk string, taking in input a C buffer pointer and length.
 *
 * The function always returns REDISMODULE_OK. */
