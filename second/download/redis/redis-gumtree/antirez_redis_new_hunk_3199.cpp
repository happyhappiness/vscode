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
