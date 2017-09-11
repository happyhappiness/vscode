    free(cmd);
}

static void test_blocking_connection(void) {
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
        strcasecmp(reply->str,"pong") == 0)
    freeReplyObject(reply);

    /* Switch to DB 9 for testing, now that we know we can chat. */
    reply = redisCommand(c,"SELECT 9");
    freeReplyObject(reply);

    /* Make sure the DB is emtpy */
    reply = redisCommand(c,"DBSIZE");
    if (reply->type != REDIS_REPLY_INTEGER || reply->integer != 0) {
        printf("Database #9 is not empty, test can not continue\n");
        exit(1);
    }
    freeReplyObject(reply);

    test("Is a able to send commands verbatim: ");
    reply = redisCommand(c,"SET foo bar");
    test_cond (reply->type == REDIS_REPLY_STATUS &&
