    return REDISMODULE_OK;
}

/* Send an integer reply to the client, with the specified long long value.
 * The function always returns REDISMODULE_OK. */
int RM_ReplyWithLongLong(RedisModuleCtx *ctx, long long ll) {
    addReplyLongLong(ctx->client,ll);
    return REDISMODULE_OK;
}

/* Reply with an error or simple string (status message). Used to implement
 * ReplyWithSimpleString() and ReplyWithError().
 * The function always returns REDISMODULE_OK. */
int replyWithStatus(RedisModuleCtx *ctx, const char *msg, char *prefix) {
    sds strmsg = sdsnewlen(prefix,1);
    strmsg = sdscat(strmsg,msg);
    strmsg = sdscatlen(strmsg,"\r\n",2);
    addReplySds(ctx->client,strmsg);
    return REDISMODULE_OK;
}

