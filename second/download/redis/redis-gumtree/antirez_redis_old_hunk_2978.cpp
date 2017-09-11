    incrDecrCommand(c,-incr);
}

void appendCommand(redisClient *c) {
    size_t totlen;
    robj *o, *append;
