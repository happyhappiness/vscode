void addReplyLongLong(redisClient *c, long long ll);
void addReplyMultiBulkLen(redisClient *c, long length);
void *dupClientReplyValue(void *o);

#ifdef __GNUC__
void addReplyErrorFormat(redisClient *c, const char *fmt, ...)
