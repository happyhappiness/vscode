 * is used, you need to call redisGetReply yourself to retrieve
 * the reply (or replies in pub/sub).
 */
void __redisAppendCommand(redisContext *c, char *cmd, size_t len) {
    c->obuf = sdscatlen(c->obuf,cmd,len);
}

void redisvAppendCommand(redisContext *c, const char *format, va_list ap) {
    char *cmd;
    int len;
    len = redisvFormatCommand(&cmd,format,ap);
    __redisAppendCommand(c,cmd,len);
    free(cmd);
}

void redisAppendCommand(redisContext *c, const char *format, ...) {
    va_list ap;
    va_start(ap,format);
    redisvAppendCommand(c,format,ap);
    va_end(ap);
}

void redisAppendCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen) {
    char *cmd;
    int len;
    len = redisFormatCommandArgv(&cmd,argc,argv,argvlen);
    __redisAppendCommand(c,cmd,len);
    free(cmd);
}

/* Helper function for the redisCommand* family of functions.
