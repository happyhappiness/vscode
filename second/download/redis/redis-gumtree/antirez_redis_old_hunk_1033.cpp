    }
    addReplyLongLong(c, waiting + (lobj ? listTypeLength(lobj) : 0));
    if (pushed) {
        char *event = (where == REDIS_HEAD) ? "lpush" : "rpush";

        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(REDIS_NOTIFY_LIST,event,c->argv[1],c->db->id);
    }
    server.dirty += pushed;
}

void lpushCommand(client *c) {
    pushGenericCommand(c,REDIS_HEAD);
}

void rpushCommand(client *c) {
    pushGenericCommand(c,REDIS_TAIL);
}

void pushxGenericCommand(client *c, robj *refval, robj *val, int where) {
