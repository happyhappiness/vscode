    }
}

static void incrDecrCommand(redisClient *c, int incr) {
    dictEntry *de;
    long long value;
