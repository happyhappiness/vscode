void redisLog(int level, const char *fmt, ...) {
    va_list ap;
    char msg[REDIS_MAX_LOGMSG_LEN];

    if (level < server.verbosity) return;

    va_start(ap, fmt);
    vsnprintf(msg, sizeof(msg), fmt, ap);
    va_end(ap);

    redisLogRaw(level,msg);
}