int redisContextConnectUnix(redisContext *c, const char *path) {
    int s;
    int blocking = (c->flags & REDIS_BLOCK);
    struct sockaddr_un sa;

    if ((s = redisCreateSocket(c,AF_LOCAL)) == REDIS_ERR)
        return REDIS_ERR;
    if (!blocking && redisSetNonBlock(c,s) != REDIS_OK)
        return REDIS_ERR;

    sa.sun_family = AF_LOCAL;
    strncpy(sa.sun_path,path,sizeof(sa.sun_path)-1);
    if (connect(s, (struct sockaddr*)&sa, sizeof(sa)) == -1) {
        if (errno == EINPROGRESS && !blocking) {
            /* This is ok. */
        } else {
            __redisSetError(c,REDIS_ERR_IO,NULL);
            close(s);
            return REDIS_ERR;
        }
    }

    c->fd = s;
    c->flags |= REDIS_CONNECTED;
    return REDIS_OK;
}