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
