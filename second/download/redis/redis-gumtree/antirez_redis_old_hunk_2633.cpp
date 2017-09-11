    server.dirty++;
}

/* MIGRATE host port key dbid timeout [COPY | REPLACE] */
void migrateCommand(redisClient *c) {
    int fd, copy = 0, replace = 0, j;
    long timeout;
    long dbid;
    long long ttl = 0, expireat;
    robj *o;
    rio cmd, payload;

    /* Parse additional options */
    for (j = 6; j < c->argc; j++) {
