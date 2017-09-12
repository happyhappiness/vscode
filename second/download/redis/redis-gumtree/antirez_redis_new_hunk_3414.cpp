
    /* Make sure the DB is emtpy */
    reply = redisCommand(c,"DBSIZE");
    if (reply->type != REDIS_REPLY_INTEGER || reply->integer != 0) {
        printf("Database #9 is not empty, test can not continue\n");
        exit(1);
    }
    freeReplyObject(reply);

