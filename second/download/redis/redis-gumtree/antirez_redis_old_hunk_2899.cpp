sds getAllClientsInfoString(void);
void rewriteClientCommandVector(redisClient *c, int argc, ...);
void rewriteClientCommandArgument(redisClient *c, int i, robj *newval);

#ifdef __GNUC__
void addReplyErrorFormat(redisClient *c, const char *fmt, ...)
