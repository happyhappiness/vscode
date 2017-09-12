void RM_Log(RedisModuleCtx *ctx, const char *levelstr, const char *fmt, ...) {
    va_list ap;
    char msg[LOG_MAX_LEN];
    size_t name_len;
    int level;

    if (!ctx->module) return;   /* Can only log if module is initialized */

    if (!strcasecmp(levelstr,"debug")) level = LL_DEBUG;
    else if (!strcasecmp(levelstr,"verbose")) level = LL_VERBOSE;
    else if (!strcasecmp(levelstr,"notice")) level = LL_NOTICE;
    else if (!strcasecmp(levelstr,"warning")) level = LL_WARNING;
    else level = LL_VERBOSE; /* Default. */

    name_len = snprintf(msg, sizeof(msg),"<%s> ", ctx->module->name);

    va_start(ap, fmt);
    vsnprintf(msg + name_len, sizeof(msg) - name_len, fmt, ap);
    va_end(ap);

    serverLogRaw(level,msg);
}