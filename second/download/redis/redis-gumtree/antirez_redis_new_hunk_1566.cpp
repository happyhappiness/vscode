        char buf[64];
        int j;

        reply = reconnectingRedisCommand(context,"INFO");
        if (reply->type == REDIS_REPLY_ERROR) {
            printf("ERROR: %s\n", reply->str);
            exit(1);
