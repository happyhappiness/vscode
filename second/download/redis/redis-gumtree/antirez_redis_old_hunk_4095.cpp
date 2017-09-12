        incrRefCount(c->argv[2]);
    }
    server.dirty++;
    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",listLength(list)));
}

static void lpushCommand(redisClient *c) {
