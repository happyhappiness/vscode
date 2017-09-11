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

static void test_reply_reader(void) {
    void *reader;
    void *reply;
    char *err;
    int ret;

    test("Error handling in reply parser: ");
    reader = redisReplyReaderCreate();
    redisReplyReaderFeed(reader,(char*)"@foo\r\n",6);
    ret = redisReplyReaderGetReply(reader,NULL);
    err = redisReplyReaderGetError(reader);
    test_cond(ret == REDIS_ERR &&
              strcasecmp(err,"Protocol error, got \"@\" as reply type byte") == 0);
    redisReplyReaderFree(reader);

    /* when the reply already contains multiple items, they must be free'd
     * on an error. valgrind will bark when this doesn't happen. */
    test("Memory cleanup in reply parser: ");
    reader = redisReplyReaderCreate();
    redisReplyReaderFeed(reader,(char*)"*2\r\n",4);
    redisReplyReaderFeed(reader,(char*)"$5\r\nhello\r\n",11);
    redisReplyReaderFeed(reader,(char*)"@foo\r\n",6);
    ret = redisReplyReaderGetReply(reader,NULL);
    err = redisReplyReaderGetError(reader);
    test_cond(ret == REDIS_ERR &&
              strcasecmp(err,"Protocol error, got \"@\" as reply type byte") == 0);
    redisReplyReaderFree(reader);

    test("Set error on nested multi bulks with depth > 1: ");
    reader = redisReplyReaderCreate();
    redisReplyReaderFeed(reader,(char*)"*1\r\n",4);
    redisReplyReaderFeed(reader,(char*)"*1\r\n",4);
    redisReplyReaderFeed(reader,(char*)"*1\r\n",4);
    ret = redisReplyReaderGetReply(reader,NULL);
    err = redisReplyReaderGetError(reader);
    test_cond(ret == REDIS_ERR &&
              strncasecmp(err,"No support for",14) == 0);
    redisReplyReaderFree(reader);

    test("Works with NULL functions for reply: ");
    reader = redisReplyReaderCreate();
    redisReplyReaderSetReplyObjectFunctions(reader,NULL);
    redisReplyReaderFeed(reader,(char*)"+OK\r\n",5);
    ret = redisReplyReaderGetReply(reader,&reply);
    test_cond(ret == REDIS_OK && reply == (void*)REDIS_REPLY_STATUS);
    redisReplyReaderFree(reader);

    test("Works when a single newline (\\r\\n) covers two calls to feed: ");
    reader = redisReplyReaderCreate();
    redisReplyReaderSetReplyObjectFunctions(reader,NULL);
    redisReplyReaderFeed(reader,(char*)"+OK\r",4);
    ret = redisReplyReaderGetReply(reader,&reply);
    assert(ret == REDIS_OK && reply == NULL);
    redisReplyReaderFeed(reader,(char*)"\n",1);
    ret = redisReplyReaderGetReply(reader,&reply);
    test_cond(ret == REDIS_OK && reply == (void*)REDIS_REPLY_STATUS);
    redisReplyReaderFree(reader);

    test("Properly reset state after protocol error: ");
    reader = redisReplyReaderCreate();
    redisReplyReaderSetReplyObjectFunctions(reader,NULL);
    redisReplyReaderFeed(reader,(char*)"x",1);
    ret = redisReplyReaderGetReply(reader,&reply);
    assert(ret == REDIS_ERR);
    ret = redisReplyReaderGetReply(reader,&reply);
    test_cond(ret == REDIS_OK && reply == NULL)
}

static void test_throughput(void) {
    int i, num;
    long long t1, t2;
    redisContext *c = blocking_context;
    redisReply **replies;

    test("Throughput:\n");
    for (i = 0; i < 500; i++)
