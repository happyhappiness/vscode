 * the initial error code. The function only provides the initial "-", so
 * the usage is, for example:
 *
 *     RedisModule_ReplyWithError(ctx,"ERR Wrong Type");
 *
 * and not just:
 *
 *     RedisModule_ReplyWithError(ctx,"Wrong Type");
 *
 * The function always returns REDISMODULE_OK.
 */
