    return REDISMODULE_OK;
}

/* Return the client object the `RM_Reply*` functions should target.
 * Normally this is just `ctx->client`, that is the client that called
 * the module command, however in the case of thread safe contexts there
 * is no directly associated client (since it would not be safe to access
 * the client from a thread), so instead the blocked client object referenced
 * in the thread safe context, has a fake client that we just use to accumulate
 * the replies. Later, when the client is unblocked, the accumulated replies
 * are appended to the actual client.
 *
 * The function returns the client pointer depending on the context, or
 * NULL if there is no potential client. This happens when we are in the
 * context of a thread safe context that was not initialized with a blocked
 * client object. */
client *moduleGetReplyClient(RedisModuleCtx *ctx) {
    if (ctx->client) return ctx->client;
    if (ctx->blocked_client) return ctx->blocked_client->reply_client;
    return NULL;
}

/* Send an integer reply to the client, with the specified long long value.
 * The function always returns REDISMODULE_OK. */
int RM_ReplyWithLongLong(RedisModuleCtx *ctx, long long ll) {
    client *c = moduleGetReplyClient(ctx);
    if (c == NULL) return REDISMODULE_OK;
    addReplyLongLong(c,ll);
    return REDISMODULE_OK;
}

/* Reply with an error or simple string (status message). Used to implement
 * ReplyWithSimpleString() and ReplyWithError().
 * The function always returns REDISMODULE_OK. */
int replyWithStatus(RedisModuleCtx *ctx, const char *msg, char *prefix) {
    client *c = moduleGetReplyClient(ctx);
    if (c == NULL) return REDISMODULE_OK;
    sds strmsg = sdsnewlen(prefix,1);
    strmsg = sdscat(strmsg,msg);
    strmsg = sdscatlen(strmsg,"\r\n",2);
    addReplySds(c,strmsg);
    return REDISMODULE_OK;
}

