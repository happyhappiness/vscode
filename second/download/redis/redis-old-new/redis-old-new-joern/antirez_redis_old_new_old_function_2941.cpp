static void test_throughput() {
    int i;
    long long t1, t2;
    redisContext *c = blocking_context;
    redisReply **replies;

    test("Throughput:\n");
    for (i = 0; i < 500; i++)
        freeReplyObject(redisCommand(c,"LPUSH mylist foo"));

    replies = malloc(sizeof(redisReply*)*1000);
    t1 = usec();
    for (i = 0; i < 1000; i++) {
        replies[i] = redisCommand(c,"PING");
        assert(replies[i] != NULL && replies[i]->type == REDIS_REPLY_STATUS);
    }
    t2 = usec();
    for (i = 0; i < 1000; i++) freeReplyObject(replies[i]);
    free(replies);
    printf("\t(1000x PING: %.2fs)\n", (t2-t1)/1000000.0);

    replies = malloc(sizeof(redisReply*)*1000);
    t1 = usec();
    for (i = 0; i < 1000; i++) {
        replies[i] = redisCommand(c,"LRANGE mylist 0 499");
        assert(replies[i] != NULL && replies[i]->type == REDIS_REPLY_ARRAY);
        assert(replies[i] != NULL && replies[i]->elements == 500);
    }
    t2 = usec();
    for (i = 0; i < 1000; i++) freeReplyObject(replies[i]);
    free(replies);
    printf("\t(1000x LRANGE with 500 elements: %.2fs)\n", (t2-t1)/1000000.0);
}