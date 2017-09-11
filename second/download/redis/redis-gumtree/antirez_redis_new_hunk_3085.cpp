}

void bgsaveCommand(redisClient *c) {
    if (server.bgsavechildpid != -1) {
        addReplyError(c,"Background save already in progress");
    } else if (server.bgrewritechildpid != -1) {
        addReplyError(c,"Can't BGSAVE while AOF log rewriting is in progress");
