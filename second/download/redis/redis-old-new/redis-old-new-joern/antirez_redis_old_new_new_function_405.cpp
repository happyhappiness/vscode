void RM_Log(RedisModuleCtx *ctx, int level, const char *fmt, ...)
{
    va_list ap;
    char msg[LOG_MAX_LEN];
    size_t name_len;

    if ((level&0xff) < server.verbosity) return;
    if (!ctx->module) return;   /* Can only log if module is initialized */

    name_len = snprintf(msg, sizeof(msg),"%s: ", ctx->module->name);

    va_start(ap, fmt);
    vsnprintf(msg + name_len, sizeof(msg) - name_len, fmt, ap);
    va_end(ap);

    serverLogRaw(level,msg);
}