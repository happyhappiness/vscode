void asyncCloseClientOnOutputBufferLimitReached(redisClient *c);
int getClientLimitClassByName(char *name);
char *getClientLimitClassName(int class);

#ifdef __GNUC__
void addReplyErrorFormat(redisClient *c, const char *fmt, ...)
