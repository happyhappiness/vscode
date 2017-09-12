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
        strcasecmp(reply->str,"ok") == 0)
    freeReplyObject(reply);

    test("%%s String interpolation works: ");
    reply = redisCommand(c,"SET %s %s","foo","hello world");
    freeReplyObject(reply);
    reply = redisCommand(c,"GET foo");
    test_cond(reply->type == REDIS_REPLY_STRING &&
        strcmp(reply->str,"hello world") == 0);
    freeReplyObject(reply);

    test("%%b String interpolation works: ");
    reply = redisCommand(c,"SET %b %b","foo",3,"hello\x00world",11);
    freeReplyObject(reply);
    reply = redisCommand(c,"GET foo");
    test_cond(reply->type == REDIS_REPLY_STRING &&
        memcmp(reply->str,"hello\x00world",11) == 0)

    test("Binary reply length is correct: ");
    test_cond(reply->len == 11)
    freeReplyObject(reply);

    test("Can parse nil replies: ");
    reply = redisCommand(c,"GET nokey");
    test_cond(reply->type == REDIS_REPLY_NIL)
    freeReplyObject(reply);

    /* test 7 */
    test("Can parse integer replies: ");
    reply = redisCommand(c,"INCR mycounter");
    test_cond(reply->type == REDIS_REPLY_INTEGER && reply->integer == 1)
    freeReplyObject(reply);

    test("Can parse multi bulk replies: ");
    freeReplyObject(redisCommand(c,"LPUSH mylist foo"));
    freeReplyObject(redisCommand(c,"LPUSH mylist bar"));
    reply = redisCommand(c,"LRANGE mylist 0 -1");
    test_cond(reply->type == REDIS_REPLY_ARRAY &&
              reply->elements == 2 &&
              !memcmp(reply->element[0]->str,"bar",3) &&
              !memcmp(reply->element[1]->str,"foo",3))
    freeReplyObject(reply);

    /* m/e with multi bulk reply *before* other reply.
     * specifically test ordering of reply items to parse. */
    test("Can handle nested multi bulk replies: ");
    freeReplyObject(redisCommand(c,"MULTI"));
    freeReplyObject(redisCommand(c,"LRANGE mylist 0 -1"));
    freeReplyObject(redisCommand(c,"PING"));
    reply = (redisCommand(c,"EXEC"));
    test_cond(reply->type == REDIS_REPLY_ARRAY &&
              reply->elements == 2 &&
              reply->element[0]->type == REDIS_REPLY_ARRAY &&
              reply->element[0]->elements == 2 &&
              !memcmp(reply->element[0]->element[0]->str,"bar",3) &&
              !memcmp(reply->element[0]->element[1]->str,"foo",3) &&
              reply->element[1]->type == REDIS_REPLY_STATUS &&
              strcasecmp(reply->element[1]->str,"pong") == 0);
    freeReplyObject(reply);

    {
        /* Find out Redis version to determine the path for the next test */
        const char *field = "redis_version:";
        char *p, *eptr;

        reply = redisCommand(c,"INFO");
        p = strstr(reply->str,field);
        major = strtol(p+strlen(field),&eptr,10);
        p = eptr+1; /* char next to the first "." */
        minor = strtol(p,&eptr,10);
        freeReplyObject(reply);
    }

    test("Returns I/O error when the connection is lost: ");
    reply = redisCommand(c,"QUIT");
    if (major >= 2 && minor > 0) {
        /* > 2.0 returns OK on QUIT and read() should be issued once more
         * to know the descriptor is at EOF. */
        test_cond(strcasecmp(reply->str,"OK") == 0 &&
            redisGetReply(c,(void**)&reply) == REDIS_ERR);
        freeReplyObject(reply);
    } else {
        test_cond(reply == NULL);
    }

    /* On 2.0, QUIT will cause the connection to be closed immediately and
     * the read(2) for the reply on QUIT will set the error to EOF.
     * On >2.0, QUIT will return with OK and another read(2) needed to be
     * issued to find out the socket was closed by the server. In both
     * conditions, the error will be set to EOF. */
    assert(c->err == REDIS_ERR_EOF &&
        strcmp(c->errstr,"Server closed the connection") == 0);
    redisFree(c);

    __connect(&c);
    test("Returns I/O error on socket timeout: ");
    struct timeval tv = { 0, 1000 };
    assert(redisSetTimeout(c,tv) == REDIS_OK);
    test_cond(redisGetReply(c,(void**)&reply) == REDIS_ERR &&
        c->err == REDIS_ERR_IO && errno == EAGAIN);
    redisFree(c);

    /* Context should be connected */
    __connect(&c);
}