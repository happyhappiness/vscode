
#define MAX_ACCEPTS_PER_CALL 1000
static void acceptCommonHandler(int fd, int flags) {
    redisClient *c;
    if ((c = createClient(fd)) == NULL) {
        serverLog(REDIS_WARNING,
            "Error registering fd event for the new client: %s (fd=%d)",
