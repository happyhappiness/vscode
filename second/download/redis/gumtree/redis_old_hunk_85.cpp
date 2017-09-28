    if (o == NULL || checkType(c,o,REDIS_LIST)) return;

    robj *value = listTypePop(o,where);
    if (value == NULL) {
        addReply(c,shared.nullbulk);
    } else {
        addReplyBulk(c,value);
        decrRefCount(value);
        if (listTypeLength(o) == 0) dbDelete(c->db,c->argv[1]);
        signalModifiedKey(c->db,c->argv[1]);
        server.dirty++;
    }
}

void lpopCommand(redisClient *c) {
