    }
}

static void zrangeGenericCommand(redisClient *c, int reverse) {
    robj *o;
    int start = atoi(c->argv[2]->ptr);
