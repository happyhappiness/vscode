    server.dirty++;
}

void setrangeCommand(redisClient *c) {
    robj *o;
    long offset;
