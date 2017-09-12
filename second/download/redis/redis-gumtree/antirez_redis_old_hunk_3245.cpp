} redisContext;

void freeReplyObject(void *reply);
void *redisReplyReaderCreate();
int redisReplyReaderSetReplyObjectFunctions(void *reader, redisReplyObjectFunctions *fn);
int redisReplyReaderSetPrivdata(void *reader, void *privdata);
void *redisReplyReaderGetObject(void *reader);
char *redisReplyReaderGetError(void *reader);
void redisReplyReaderFree(void *ptr);
void redisReplyReaderFeed(void *reader, char *buf, size_t len);
int redisReplyReaderGetReply(void *reader, void **reply);

/* Functions to format a command according to the protocol. */
