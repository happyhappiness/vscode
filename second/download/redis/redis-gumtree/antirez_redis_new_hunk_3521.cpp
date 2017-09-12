    addReplyLongLong(c,totlen);
}

void strlenCommand(redisClient *c) {
    robj *o;

