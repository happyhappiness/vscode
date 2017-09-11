}

void addReplyErrorFormat(redisClient *c, const char *fmt, ...) {
    va_list ap;
    va_start(ap,fmt);
    sds s = sdscatvprintf(sdsempty(),fmt,ap);
    va_end(ap);
    _addReplyError(c,s,sdslen(s));
    sdsfree(s);
}
