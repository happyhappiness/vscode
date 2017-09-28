    ret = redisvAppendCommand(c,format,ap);
    va_end(ap);
    return ret;
}

int redisAppendCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen) {
    char *cmd;
    int len;

    len = redisFormatCommandArgv(&cmd,argc,argv,argvlen);
    if (len == -1) {
        __redisSetError(c,REDIS_ERR_OOM,"Out of memory");
        return REDIS_ERR;
    }

    if (__redisAppendCommand(c,cmd,len) != REDIS_OK) {
        free(cmd);
        return REDIS_ERR;
    }

    free(cmd);
    return REDIS_OK;
}

/* Helper function for the redisCommand* family of functions.
 *
 * Write a formatted command to the output buffer. If the given context is
 * blocking, immediately read the reply into the "reply" pointer. When the
 * context is non-blocking, the "reply" pointer will not be used and the
 * command is simply appended to the write buffer.
 *
 * Returns the reply when a reply was succesfully retrieved. Returns NULL
 * otherwise. When NULL is returned in a blocking context, the error field
 * in the context will be set.
 */
static void *__redisBlockForReply(redisContext *c) {
    void *reply;

