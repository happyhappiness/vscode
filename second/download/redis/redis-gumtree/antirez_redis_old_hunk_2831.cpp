        cmd[pos++] = '\n';
    }
    assert(pos == totlen);
    cmd[totlen] = '\0';
    *target = cmd;
    return totlen;
}

void __redisSetError(redisContext *c, int type, const sds errstr) {
    c->err = type;
    if (errstr != NULL) {
        c->errstr = errstr;
    } else {
        /* Only REDIS_ERR_IO may lack a description! */
        assert(type == REDIS_ERR_IO);
        c->errstr = sdsnew(strerror(errno));
    }
}

static redisContext *redisContextInit(void) {
    redisContext *c = calloc(sizeof(redisContext),1);
    c->err = 0;
    c->errstr = NULL;
    c->obuf = sdsempty();
    c->fn = &defaultFunctions;
    c->reader = NULL;
    return c;
}

void redisFree(redisContext *c) {
    if (c->fd > 0)
        close(c->fd);
    if (c->errstr != NULL)
        sdsfree(c->errstr);
    if (c->obuf != NULL)
        sdsfree(c->obuf);
    if (c->reader != NULL)
        redisReplyReaderFree(c->reader);
    free(c);
}

