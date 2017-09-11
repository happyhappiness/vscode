        dbAdd(c->db,dstkey,dstobj);
        addReplyLongLong(c,zsetLength(dstobj));
        if (!touched) signalModifiedKey(c->db,dstkey);
        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,
            (op == REDIS_OP_UNION) ? "zunionstore" : "zinterstore",
            dstkey,c->db->id);
        server.dirty++;
    } else {
        decrRefCount(dstobj);
        addReply(c,shared.czero);
        if (touched)
            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",dstkey,c->db->id);
    }
    zfree(src);
}

void zunionstoreCommand(client *c) {
    zunionInterGenericCommand(c,c->argv[1], REDIS_OP_UNION);
}

void zinterstoreCommand(client *c) {
    zunionInterGenericCommand(c,c->argv[1], REDIS_OP_INTER);
}

void zrangeGenericCommand(client *c, int reverse) {
