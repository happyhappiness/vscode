 *     return RM_ReplyWithLongLong(ctx,mycount);
 * -------------------------------------------------------------------------- */

/* Send an error about the number of arguments given to the command,
 * citing the command name in the error message.
 *
 * Example:
 *
 *  if (argc != 3) return RedisModule_WrongArity(ctx);
 */
int RM_WrongArity(RedisModuleCtx *ctx) {
    addReplyErrorFormat(ctx->client,
        "wrong number of arguments for '%s' command",
        (char*)ctx->client->argv[0]->ptr);
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
