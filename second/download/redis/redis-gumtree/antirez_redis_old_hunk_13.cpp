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
