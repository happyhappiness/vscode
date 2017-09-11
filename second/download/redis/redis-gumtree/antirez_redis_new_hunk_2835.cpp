    void (*freeObject)(void*);
} redisReplyObjectFunctions;

/* State for the protocol parser */
typedef struct redisReader {
    int err; /* Error flags, 0 when there is no error */
    char errstr[128]; /* String representation of error when applicable */

    char *buf; /* Read buffer */
    size_t pos; /* Buffer cursor */
    size_t len; /* Buffer length */

    redisReadTask rstack[4];
    int ridx; /* Index of current read task */
    void *reply; /* Temporary reply pointer */

    redisReplyObjectFunctions *fn;
    void *privdata;
} redisReader;

/* Public API for the protocol parser. */
redisReader *redisReaderCreate(void);
void redisReaderFree(redisReader *r);
int redisReaderFeed(redisReader *r, const char *buf, size_t len);
int redisReaderGetReply(redisReader *r, void **reply);

/* Backwards compatibility, can be removed on big version bump. */
#define redisReplyReaderCreate redisReaderCreate
#define redisReplyReaderFree redisReaderFree
#define redisReplyReaderFeed redisReaderFeed
#define redisReplyReaderGetReply redisReaderGetReply
#define redisReplyReaderSetPrivdata(_r, _p) (int)(((redisReader*)(_r))->privdata = (_p))
#define redisReplyReaderGetObject(_r) (((redisReader*)(_r))->reply)
#define redisReplyReaderGetError(_r) (((redisReader*)(_r))->errstr)

/* Function to free the reply objects hiredis returns by default. */
void freeReplyObject(void *reply);

/* Functions to format a command according to the protocol. */
int redisvFormatCommand(char **target, const char *format, va_list ap);
int redisFormatCommand(char **target, const char *format, ...);
int redisFormatCommandArgv(char **target, int argc, const char **argv, const size_t *argvlen);

/* Context for a connection to Redis */
typedef struct redisContext {
    int err; /* Error flags, 0 when there is no error */
    char errstr[128]; /* String representation of error when applicable */
    int fd;
    int flags;
    char *obuf; /* Write buffer */
    redisReader *reader; /* Protocol reader */
} redisContext;

redisContext *redisConnect(const char *ip, int port);
redisContext *redisConnectWithTimeout(const char *ip, int port, struct timeval tv);
redisContext *redisConnectNonBlock(const char *ip, int port);
redisContext *redisConnectUnix(const char *path);
redisContext *redisConnectUnixWithTimeout(const char *path, struct timeval tv);
redisContext *redisConnectUnixNonBlock(const char *path);
int redisSetTimeout(redisContext *c, struct timeval tv);
void redisFree(redisContext *c);
int redisBufferRead(redisContext *c);
int redisBufferWrite(redisContext *c, int *done);
