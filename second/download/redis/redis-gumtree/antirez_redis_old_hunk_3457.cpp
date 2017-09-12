    ret = redisReplyReaderGetReply(reader,NULL);
    err = redisReplyReaderGetError(reader);
    test_cond(ret == REDIS_ERR &&
              strcasecmp(err,"protocol error, got \"@\" as reply type byte") == 0);
    redisReplyReaderFree(reader);

    /* when the reply already contains multiple items, they must be free'd
