        printf("\n");
        freeReplyObject(reply);
        usleep(config.interval);
    }
}

static void scanMode() {
    redisReply *reply;
    unsigned long long cur = 0;

    do {
        if (config.pattern)
