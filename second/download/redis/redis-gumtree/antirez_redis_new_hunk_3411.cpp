void freeReplyObject(void *reply);
void *redisReplyReaderCreate();
int redisReplyReaderSetReplyObjectFunctions(void *reader, redisReplyObjectFunctions *fn);
int redisReplyReaderSetPrivdata(void *reader, void *privdata);
void *redisReplyReaderGetObject(void *reader);
char *redisReplyReaderGetError(void *reader);
void redisReplyReaderFree(void *ptr);
