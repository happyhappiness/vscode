        pushed++;
    }
    addReplyLongLong(c, waiting + (lobj ? listTypeLength(lobj) : 0));
    if (pushed) {
        char *event = (where == REDIS_HEAD) ? "lpush" : "rpush";

        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(event,c->argv[1],c->db->id);
    }
    server.dirty += pushed;
}

