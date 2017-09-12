        matches++;
    }
    decrRefCount(o);
    setDeferredMultiBulkLength(c,replylen,matches*2);
}

void configCommand(redisClient *c) {
