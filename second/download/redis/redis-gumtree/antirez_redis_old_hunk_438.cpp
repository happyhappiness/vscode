 * 'return' in order to return from the command implementation with:
 *
 * if (... some condition ...)
 *     return RedisModule_ReplyWithLongLong(ctx,mycount);
 * -------------------------------------------------------------------------- */

/* Send an error about the number of arguments given to the command. */
int RedisModule_WrongArity(RedisModuleCtx *ctx) {
    addReplyErrorFormat(ctx->client,
        "wrong number of arguments for '%s' command",
        (char*)ctx->client->argv[0]->ptr);
