    if (maxlen) {
        o = createObject(REDIS_STRING,res);
        setKey(c->db,targetkey,o);
        notifyKeyspaceEvent("set",targetkey,c->db->id);
        decrRefCount(o);
    } else if (dbDelete(c->db,targetkey)) {
        signalModifiedKey(c->db,targetkey);
        notifyKeyspaceEvent("del",targetkey,c->db->id);
    }
    server.dirty++;
    addReplyLongLong(c,maxlen); /* Return the output string length in bytes. */
