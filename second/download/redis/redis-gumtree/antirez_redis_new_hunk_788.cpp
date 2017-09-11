    if (maxlen) {
        o = createObject(OBJ_STRING,res);
        setKey(c->db,targetkey,o);
        notifyKeyspaceEvent(NOTIFY_STRING,"set",targetkey,c->db->id);
        decrRefCount(o);
    } else if (dbDelete(c->db,targetkey)) {
        signalModifiedKey(c->db,targetkey);
        notifyKeyspaceEvent(NOTIFY_GENERIC,"del",targetkey,c->db->id);
    }
    server.dirty++;
    addReplyLongLong(c,maxlen); /* Return the output string length in bytes. */
