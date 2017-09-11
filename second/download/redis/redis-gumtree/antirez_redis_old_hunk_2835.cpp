    void (*freeObject)(void*);
} redisReplyObjectFunctions;

struct redisContext; /* need forward declaration of redisContext */

/* Context for a connection to Redis */
typedef struct redisContext {
    int fd;
    int flags;
    char *obuf; /* Write buffer */
    int err; /* Error flags, 0 when there is no error */
    char *errstr; /* String representation of error when applicable */

    /* Function set for reply buildup and reply reader */
    redisReplyObjectFunctions *fn;
    void *reader;
} redisContext;

void freeReplyObject(void *reply);
void *redisReplyReaderCreate(void);
int redisReplyReaderSetReplyObjectFunctions(void *reader, redisReplyObjectFunctions *fn);
int redisReplyReaderSetPrivdata(void *reader, void *privdata);
void *redisReplyReaderGetObject(void *reader);
char *redisReplyReaderGetError(void *reader);
void redisReplyReaderFree(void *ptr);
void redisReplyReaderFeed(void *reader, const char *buf, size_t len);
int redisReplyReaderGetReply(void *reader, void **reply);

/* Functions to format a command according to the protocol. */
int redisvFormatCommand(char **target, const char *format, va_list ap);
int redisFormatCommand(char **target, const char *format, ...);
int redisFormatCommandArgv(char **target, int argc, const char **argv, const size_t *argvlen);

redisContext *redisConnect(const char *ip, int port);
redisContext *redisConnectWithTimeout(const char *ip, int port, struct timeval tv);
redisContext *redisConnectNonBlock(const char *ip, int port);
redisContext *redisConnectUnix(const char *path);
redisContext *redisConnectUnixWithTimeout(const char *path, struct timeval tv);
redisContext *redisConnectUnixNonBlock(const char *path);
int redisSetTimeout(redisContext *c, struct timeval tv);
int redisSetReplyObjectFunctions(redisContext *c, redisReplyObjectFunctions *fn);
void redisFree(redisContext *c);
int redisBufferRead(redisContext *c);
int redisBufferWrite(redisContext *c, int *done);
