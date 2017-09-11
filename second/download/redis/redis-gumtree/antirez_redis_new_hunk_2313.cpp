char *getClientLimitClassName(int class);
void flushSlavesOutputBuffers(void);
void disconnectSlaves(void);
int listenToPort(int port, int *fds, int *count);

#ifdef __GNUC__
void addReplyErrorFormat(redisClient *c, const char *fmt, ...)
