void alsoPropagate(struct redisCommand *cmd, int dbid, robj **argv, int argc, int target);
void forceCommandPropagation(client *c, int flags);
void preventCommandPropagation(client *c);
int prepareForShutdown();
#ifdef __GNUC__
void serverLog(int level, const char *fmt, ...)
