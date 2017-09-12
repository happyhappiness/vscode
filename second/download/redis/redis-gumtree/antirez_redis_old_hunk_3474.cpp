
    /* PING server */
    reply = redisCommand(c,"PING");
    printf("PONG: %s\n", reply->str);
    freeReplyObject(reply);

    /* Set a key */
