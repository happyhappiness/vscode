}

void _redisAssertPrintClientInfo(redisClient *c) {
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

void _redisAssertPrintObject(robj *o) {
    redisLog(REDIS_WARNING,"=== ASSERTION FAILED OBJECT CONTEXT ===");
    redisLog(REDIS_WARNING,"Object type: %d", o->type);
    redisLog(REDIS_WARNING,"Object encoding: %d", o->encoding);
    redisLog(REDIS_WARNING,"Object refcount: %d", o->refcount);
    if (o->type == REDIS_STRING && o->encoding == REDIS_ENCODING_RAW) {
        redisLog(REDIS_WARNING,"Object raw string len: %d", sdslen(o->ptr));
        if (sdslen(o->ptr) < 4096)
            redisLog(REDIS_WARNING,"Object raw string content: \"%s\"", (char*)o->ptr);
    }
}

void _redisAssertWithInfo(redisClient *c, robj *o, char *estr, char *file, int line) {
    if (c) _redisAssertPrintClientInfo(c);
    if (o) _redisAssertPrintObject(o);
    _redisAssert(estr,file,line);
}

