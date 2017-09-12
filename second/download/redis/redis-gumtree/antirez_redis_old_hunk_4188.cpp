    }
}

static void hdelCommand(redisClient *c) {
    robj *o;
    int deleted = 0;
