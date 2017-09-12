
    /* Make sure the DB is emtpy */
    reply = redisCommand(c,"DBSIZE");
    if (reply->type != REDIS_REPLY_INTEGER ||
        reply->integer != 0) {
        printf("Sorry DB 9 is not empty, test can not continue\n");
        exit(1);
    } else {
        printf("DB 9 is empty... test can continue\n");
    }
    freeReplyObject(reply);

