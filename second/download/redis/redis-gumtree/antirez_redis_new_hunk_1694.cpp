void addReplyBulkLongLong(redisClient *c, long long ll);
void addReply(redisClient *c, robj *obj);
void addReplySds(redisClient *c, sds s);
void addReplyBulkSds(redisClient *c, sds s);
void addReplyError(redisClient *c, char *err);
void addReplyStatus(redisClient *c, char *status);
void addReplyDouble(redisClient *c, double d);
