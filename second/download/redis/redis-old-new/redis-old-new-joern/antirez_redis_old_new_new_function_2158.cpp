void hdelCommand(redisClient *c) {
    robj *o;
    int j, deleted = 0, keyremoved = 0;

    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_HASH)) return;

    for (j = 2; j < c->argc; j++) {
        if (hashTypeDelete(o,c->argv[j])) {
            deleted++;
            if (hashTypeLength(o) == 0) {
                dbDelete(c->db,c->argv[1]);
                keyremoved = 1;
                break;
            }
        }
    }
    if (deleted) {
        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent(REDIS_NOTIFY_HASH,"hdel",c->argv[1],c->db->id);
        if (keyremoved)
            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],
                                c->db->id);
        server.dirty += deleted;
    }
    addReplyLongLong(c,deleted);
}