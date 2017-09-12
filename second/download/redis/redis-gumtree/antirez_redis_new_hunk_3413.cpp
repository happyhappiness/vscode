
    test("Format command by passing argc/argv with lengths: ");
    len = redisFormatCommandArgv(&cmd,argc,argv,lens);
    test_cond(strncmp(cmd,"*3\r\n$3\r\nSET\r\n$7\r\nfoo\0xxx\r\n$3\r\nbar\r\n",len) == 0 &&
        len == 4+4+(3+2)+4+(7+2)+4+(3+2));
    free(cmd);
}

static void test_blocking_connection() {
    redisContext *c;
    redisReply *reply;
    int major, minor;

    test("Returns error when host cannot be resolved: ");
    c = redisConnect((char*)"idontexist.local", 6379);
    test_cond(c->err == REDIS_ERR_OTHER &&
        strcmp(c->errstr,"Can't resolve: idontexist.local") == 0);
    redisFree(c);

    test("Returns error when the port is not open: ");
    c = redisConnect((char*)"localhost", 56380);
    test_cond(c->err == REDIS_ERR_IO &&
        strcmp(c->errstr,"Connection refused") == 0);
    redisFree(c);

    __connect(&c);
    test("Is able to deliver commands: ");
    reply = redisCommand(c,"PING");
    test_cond(reply->type == REDIS_REPLY_STATUS &&
