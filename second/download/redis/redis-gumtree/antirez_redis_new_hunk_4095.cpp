        incrRefCount(c->argv[2]);
    }
    server.dirty++;
    addReplyLongLong(c,listLength(list));
}

static void lpushCommand(redisClient *c) {
