void pushxGenericCommand(client *c, int where) {
    robj *subject;

    if ((subject = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,subject,OBJ_LIST)) return;

    char *event = (where == LIST_HEAD) ? "lpush" : "rpush";
    c->argv[2] = tryObjectEncoding(c->argv[2]);
    listTypePush(subject,c->argv[2],where);
    signalModifiedKey(c->db,c->argv[1]);
    notifyKeyspaceEvent(NOTIFY_LIST,event,c->argv[1],c->db->id);
    server.dirty++;

    addReplyLongLong(c,listTypeLength(subject));
}