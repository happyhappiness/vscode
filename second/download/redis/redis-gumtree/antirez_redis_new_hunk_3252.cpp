    for (i = 0; i < 500; i++)
        freeReplyObject(redisCommand(c,"LPUSH mylist foo"));

    num = 1000;
    replies = malloc(sizeof(redisReply*)*num);
    t1 = usec();
    for (i = 0; i < num; i++) {
        replies[i] = redisCommand(c,"PING");
        assert(replies[i] != NULL && replies[i]->type == REDIS_REPLY_STATUS);
    }
    t2 = usec();
    for (i = 0; i < num; i++) freeReplyObject(replies[i]);
    free(replies);
    printf("\t(%dx PING: %.3fs)\n", num, (t2-t1)/1000000.0);

    replies = malloc(sizeof(redisReply*)*num);
    t1 = usec();
    for (i = 0; i < num; i++) {
        replies[i] = redisCommand(c,"LRANGE mylist 0 499");
        assert(replies[i] != NULL && replies[i]->type == REDIS_REPLY_ARRAY);
        assert(replies[i] != NULL && replies[i]->elements == 500);
    }
    t2 = usec();
    for (i = 0; i < num; i++) freeReplyObject(replies[i]);
    free(replies);
    printf("\t(%dx LRANGE with 500 elements: %.3fs)\n", num, (t2-t1)/1000000.0);

    num = 10000;
    replies = malloc(sizeof(redisReply*)*num);
    for (i = 0; i < num; i++)
        redisAppendCommand(c,"PING");
    t1 = usec();
    for (i = 0; i < num; i++) {
        assert(redisGetReply(c, (void*)&replies[i]) == REDIS_OK);
        assert(replies[i] != NULL && replies[i]->type == REDIS_REPLY_STATUS);
    }
    t2 = usec();
    for (i = 0; i < num; i++) freeReplyObject(replies[i]);
    free(replies);
    printf("\t(%dx PING (pipelined): %.3fs)\n", num, (t2-t1)/1000000.0);

    replies = malloc(sizeof(redisReply*)*num);
    for (i = 0; i < num; i++)
        redisAppendCommand(c,"LRANGE mylist 0 499");
    t1 = usec();
    for (i = 0; i < num; i++) {
        assert(redisGetReply(c, (void*)&replies[i]) == REDIS_OK);
        assert(replies[i] != NULL && replies[i]->type == REDIS_REPLY_ARRAY);
        assert(replies[i] != NULL && replies[i]->elements == 500);
    }
    t2 = usec();
    for (i = 0; i < num; i++) freeReplyObject(replies[i]);
    free(replies);
    printf("\t(%dx LRANGE with 500 elements (pipelined): %.3fs)\n", num, (t2-t1)/1000000.0);
}

static void cleanup(void) {
    redisContext *c = blocking_context;
    redisReply *reply;

