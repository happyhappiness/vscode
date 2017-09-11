 * Logging
 * -------------------------------------------------------------------------- */

/* This is the low level function implementing both:
 *
 *  RM_Log()
 *  RM_LogIOError()
 *
 */
void RM_LogRaw(RedisModule *module, const char *levelstr, const char *fmt, va_list ap) {
    char msg[LOG_MAX_LEN];
    size_t name_len;
    int level;

    if (!strcasecmp(levelstr,"debug")) level = LL_DEBUG;
    else if (!strcasecmp(levelstr,"verbose")) level = LL_VERBOSE;
    else if (!strcasecmp(levelstr,"notice")) level = LL_NOTICE;
    else if (!strcasecmp(levelstr,"warning")) level = LL_WARNING;
    else level = LL_VERBOSE; /* Default. */

    name_len = snprintf(msg, sizeof(msg),"<%s> ", module->name);
    vsnprintf(msg + name_len, sizeof(msg) - name_len, fmt, ap);
    serverLogRaw(level,msg);
}

/*
 * Produces a log message to the standard Redis log, the format accepts
 * printf-alike specifiers, while level is a string describing the log
 * level to use when emitting the log, and must be one of the following:
 *
