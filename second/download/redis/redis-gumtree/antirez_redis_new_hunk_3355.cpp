}

void saveCommand(redisClient *c) {
    if (server.bgsavechildpid != -1 || server.bgsavethread != (pthread_t)-1) {
        addReplyError(c,"Background save already in progress");
        return;
    }
