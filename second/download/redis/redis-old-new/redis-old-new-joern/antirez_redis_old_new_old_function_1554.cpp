static redisContext *connect(struct config config) {
    redisContext *c = NULL;

    if (config.type == CONN_TCP) {
        c = redisConnect(config.tcp.host, config.tcp.port);
    } else if (config.type == CONN_UNIX) {
        c = redisConnectUnix(config.unix.path);
    } else {
        assert(NULL);
    }

    if (c->err) {
        printf("Connection error: %s\n", c->errstr);
        exit(1);
    }

    return select_database(c);
}