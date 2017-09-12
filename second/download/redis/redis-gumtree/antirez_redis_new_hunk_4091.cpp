        (unsigned long) strlen(buf),buf));
}

static void addReplyLongLong(redisClient *c, long long ll) {
    char buf[128];
    size_t len;
