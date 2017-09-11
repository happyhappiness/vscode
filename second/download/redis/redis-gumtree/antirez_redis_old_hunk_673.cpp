    value += incr;

    char buf[256];
    int len = ld2string(buf,sizeof(buf),value,humanfriendly);
    new = sdsnewlen(buf,len);
    hashTypeSet(o,c->argv[2],new);
    addReplyBulkSds(c,new);
    signalModifiedKey(c->db,c->argv[1]);
    notifyKeyspaceEvent(NOTIFY_HASH,"hincrbyfloat",c->argv[1],c->db->id);
