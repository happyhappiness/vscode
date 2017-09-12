} redisContext;

void freeReplyObject(void *reply);
void *redisReplyReaderCreate(redisReplyObjectFunctions *fn);
void *redisReplyReaderGetObject(void *reader);
char *redisReplyReaderGetError(void *reader);
void redisReplyReaderFree(void *ptr);
