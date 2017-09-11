        addReplyError(c,"The specified key does not exist");
        return;
    } else {
        if (isHLLObjectOrReply(c,o) != REDIS_OK) return;

        registers = o->ptr;
        addReplyMultiBulkLen(c,REDIS_HLL_REGISTERS);
