        incrRefCount(c->argv[2]);
    }
    server.dirty++;
    addReply(c,shared.ok);
}

static void lpushCommand(redisClient *c) {
