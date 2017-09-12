void pushGenericCommand(redisClient *c, int where) {
    int j, waiting = 0, pushed = 0;
    robj *lobj = lookupKeyWrite(c->db,c->argv[1]);
    int may_have_waiting_clients = (lobj == NULL);

    if (lobj && lobj->type != REDIS_LIST) {
        addReply(c,shared.wrongtypeerr);
        return;
    }

    if (may_have_waiting_clients) signalListAsReady(c,c->argv[1]);

    for (j = 2; j < c->argc; j++) {
        c->argv[j] = tryObjectEncoding(c->argv[j]);
        if (!lobj) {
            lobj = createZiplistObject();
            dbAdd(c->db,c->argv[1],lobj);
        }
        listTypePush(lobj,c->argv[j],where);
        pushed++;
    }
    addReplyLongLong(c, waiting + (lobj ? listTypeLength(lobj) : 0));
    if (pushed) signalModifiedKey(c->db,c->argv[1]);
    server.dirty += pushed;
}