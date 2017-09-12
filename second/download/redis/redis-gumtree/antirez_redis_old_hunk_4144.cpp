    }
    decrRefCount(o);
    addReply(c,shared.ok);
}

static void configGetCommand(redisClient *c) {
