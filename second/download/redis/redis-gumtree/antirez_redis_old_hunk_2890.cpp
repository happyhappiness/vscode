unsigned long getClientOutputBufferMemoryUsage(redisClient *c);
void freeClientsInAsyncFreeQueue(void);
void asyncCloseClientOnOutputBufferLimitReached(redisClient *c);

#ifdef __GNUC__
void addReplyErrorFormat(redisClient *c, const char *fmt, ...)
