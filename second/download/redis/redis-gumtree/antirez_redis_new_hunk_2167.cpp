void flushSlavesOutputBuffers(void);
void disconnectSlaves(void);
int listenToPort(int port, int *fds, int *count);
void pauseClients(mstime_t duration);
int clientsArePaused(void);

#ifdef __GNUC__
void addReplyErrorFormat(redisClient *c, const char *fmt, ...)
