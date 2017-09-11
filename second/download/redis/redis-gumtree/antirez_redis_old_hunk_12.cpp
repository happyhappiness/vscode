 * Most functions always return REDISMODULE_OK so you can use it with
 * 'return' in order to return from the command implementation with:
 *
 * if (... some condition ...)
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
