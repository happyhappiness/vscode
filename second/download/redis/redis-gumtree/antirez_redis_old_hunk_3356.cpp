}

void bgsaveCommand(redisClient *c) {
    if (server.bgsavechildpid != -1 || server.bgsavethread != (pthread-t)-1) {
        addReplyError(c,"Background save already in progress");
        return;
    }
