    signalModifiedKey(c->db,c->argv[1]);
    /* We generate an PFADD event for PFMERGE for semantical simplicity
     * since in theory this is a mass-add of elements. */
    notifyKeyspaceEvent(NOTIFY_STRING,"pfadd",c->argv[1],c->db->id);
    server.dirty++;
    addReply(c,shared.ok);
}
