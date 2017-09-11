#define AF_LOCAL AF_UNIX
#endif

int redisCheckSocketError(redisContext *c, int fd);
int redisContextSetTimeout(redisContext *c, struct timeval tv);
int redisContextConnectTcp(redisContext *c, const char *addr, int port, struct timeval *timeout);
int redisContextConnectUnix(redisContext *c, const char *path, struct timeval *timeout);

#endif
