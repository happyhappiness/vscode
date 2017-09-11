    server.dirty++;
}

/* MIGRATE host port key dbid timeout [COPY | REPLACE] */
void migrateCommand(redisClient *c) {
    int fd, copy = 0, replace = 0, j;
