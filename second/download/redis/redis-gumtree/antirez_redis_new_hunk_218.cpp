 * a few lines of text.
 */
void RM_Log(RedisModuleCtx *ctx, const char *levelstr, const char *fmt, ...) {
    if (!ctx->module) return;   /* Can only log if module is initialized */

    va_list ap;
    va_start(ap, fmt);
    RM_LogRaw(ctx->module,levelstr,fmt,ap);
    va_end(ap);
}

/* Log errors from RDB / AOF serialization callbacks.
 *
 * This function should be used when a callback is returning a critical
 * error to the caller since cannot load or save the data for some
 * critical reason. */
void RM_LogIOError(RedisModuleIO *io, const char *levelstr, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    RM_LogRaw(io->type->module,levelstr,fmt,ap);
    va_end(ap);
}

/* --------------------------------------------------------------------------
