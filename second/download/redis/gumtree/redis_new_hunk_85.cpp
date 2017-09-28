    if (o == NULL || checkType(c,o,REDIS_LIST)) return;

    robj *value = listTypePop(o,where);
    if (value == NULL) {
        addReply(c,shared.nullbulk);
    } else {
        char *event = (where == REDIS_HEAD) ? "lpop" : "rpop";

        addReplyBulk(c,value);
        decrRefCount(value);
        notifyKeyspaceEvent(REDIS_NOTIFY_LIST,event,c->argv[1],c->db->id);
        if (listTypeLength(o) == 0) {
            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",
                                c->argv[1],c->db->id);
            dbDelete(c->db,c->argv[1]);
        }
        signalModifiedKey(c->db,c->argv[1]);
        server.dirty++;
    }
}

void lpopCommand(redisClient *c) {
