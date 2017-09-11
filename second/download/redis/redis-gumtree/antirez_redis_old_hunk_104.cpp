    c->errstr[0] = '\0';
    c->obuf = sdsempty();
    c->reader = redisReaderCreate();
    return c;
}

void redisFree(redisContext *c) {
    if (c->fd > 0)
        close(c->fd);
    if (c->obuf != NULL)
        sdsfree(c->obuf);
    if (c->reader != NULL)
        redisReaderFree(c->reader);
    free(c);
}

int redisFreeKeepFd(redisContext *c) {
	int fd = c->fd;
	c->fd = -1;
	redisFree(c);
	return fd;
}

/* Connect to a Redis instance. On error the field error in the returned
