    if (value == NULL) {
        addReply(c,shared.nullbulk);
    } else {
        char *event = (where == REDIS_HEAD) ? "lpop" : "rpop";

        addReplyBulk(c,value);
        decrRefCount(value);
        notifyKeyspaceEvent(event,c->argv[1],c->db->id);
        if (listTypeLength(o) == 0) {
            notifyKeyspaceEvent("del",c->argv[1],c->db->id);
            dbDelete(c->db,c->argv[1]);
        }
        signalModifiedKey(c->db,c->argv[1]);
        server.dirty++;
    }
