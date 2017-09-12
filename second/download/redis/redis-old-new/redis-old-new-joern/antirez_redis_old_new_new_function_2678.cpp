void _redisAssertPrintClientInfo(redisClient *c) {
    if (c) {
        int j;

        redisLog(REDIS_WARNING,"=== ASSERTION FAILED CLIENT CONTEXT ===");
        redisLog(REDIS_WARNING,"client->flags = %d", c->flags);
        redisLog(REDIS_WARNING,"client->fd = %d", c->fd);
        redisLog(REDIS_WARNING,"client->argc = %d", c->argc);
        for (j=0; j < c->argc; j++) {
            char buf[128];
            char *arg;

            if (c->argv[j]->type == REDIS_STRING &&
                c->argv[j]->encoding == REDIS_ENCODING_RAW)
            {
                arg = (char*) c->argv[j]->ptr;
            } else {
                snprintf(buf,sizeof(buf),"Object type: %d, encoding: %d",
                    c->argv[j]->type, c->argv[j]->encoding);
                arg = buf;
            }
            redisLog(REDIS_WARNING,"client->argv[%d] = \"%s\" (refcount: %d)",
                j, arg, c->argv[j]->refcount);
        }
    }
}