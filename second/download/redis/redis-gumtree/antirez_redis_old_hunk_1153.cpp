#endif

/* Debugging stuff */
void _redisAssertWithInfo(client *c, robj *o, char *estr, char *file, int line);
void _redisAssert(char *estr, char *file, int line);
void _redisPanic(char *msg, char *file, int line);
void bugReportStart(void);
void serverLogObjectDebugInfo(robj *o);
