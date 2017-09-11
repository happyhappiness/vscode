    for (i = 0; i < num; i++) freeReplyObject(replies[i]);
    free(replies);
    printf("\t(%dx LRANGE with 500 elements (pipelined): %.3fs)\n", num, (t2-t1)/1000000.0);
}

static void cleanup(void) {
    redisContext *c = blocking_context;
    redisReply *reply;

    /* Make sure we're on DB 9 */
    reply = redisCommand(c,"SELECT 9");
    assert(reply != NULL); freeReplyObject(reply);
    reply = redisCommand(c,"FLUSHDB");
    assert(reply != NULL); freeReplyObject(reply);
    redisFree(c);
}

// static long __test_callback_flags = 0;
