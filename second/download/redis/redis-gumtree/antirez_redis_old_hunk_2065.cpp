    addReplyLongLong(c, count);
}

void zcardCommand(redisClient *c) {
    robj *key = c->argv[1];
    robj *zobj;
