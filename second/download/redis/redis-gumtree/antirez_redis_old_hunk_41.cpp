 * that is not easy to calculate in advance the number of elements.
 */
void RM_ReplySetArrayLength(RedisModuleCtx *ctx, long len) {
    if (ctx->postponed_arrays_count == 0) {
        serverLog(LL_WARNING,
            "API misuse detected in module %s: "
