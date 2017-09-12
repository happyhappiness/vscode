
    test("Format command by passing argc/argv with lengths: ");
    len = redisFormatCommandArgv(&cmd,argc,argv,lens);
    test_cond(strncmp(cmd,"*3\r\n$3\r\nSET\r\n$3\r\nfoo\r\n$3\r\nbar\r\n",len) == 0 &&
        len == 4+4+(3+2)+4+(3+2)+4+(3+2));
    free(cmd);
}

static void test_blocking_connection() {
    redisContext *c;
    redisReply *reply;

    __connect(&c);
    test("Returns I/O error when the connection is lost: ");
    reply = redisCommand(c,"QUIT");
    test_cond(strcasecmp(reply->str,"OK") == 0 && redisCommand(c,"PING") == NULL);

    /* Two conditions may happen, depending on the type of connection.
     * When connected via TCP, the socket will not yet be aware of the closed
     * connection and the write(2) call will succeed, but the read(2) will
     * result in an EOF. When connected via Unix sockets, the socket will be
     * immediately aware that it was closed and fail on the write(2) call. */
    if (use_unix) {
        fprintf(stderr,"Error: %s\n", c->errstr);
        assert(c->err == REDIS_ERR_IO &&
            strcmp(c->errstr,"Broken pipe") == 0);
    } else {
        fprintf(stderr,"Error: %s\n", c->errstr);
        assert(c->err == REDIS_ERR_EOF &&
            strcmp(c->errstr,"Server closed the connection") == 0);
    }
    freeReplyObject(reply);
    redisFree(c);

    __connect(&c); /* reconnect */
    test("Is able to deliver commands: ");
    reply = redisCommand(c,"PING");
    test_cond(reply->type == REDIS_REPLY_STATUS &&
