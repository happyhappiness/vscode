#define AF_LOCAL AF_UNIX
#endif

int redisContextSetTimeout(redisContext *c, struct timeval tv);
int redisContextConnectTcp(redisContext *c, const char *addr, int port, struct timeval *timeout);
int redisContextConnectUnix(redisContext *c, const char *path, struct timeval *timeout);
