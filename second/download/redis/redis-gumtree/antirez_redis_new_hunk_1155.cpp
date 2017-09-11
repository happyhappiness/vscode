
    /* Store the computed value into the target key */
    if (maxlen) {
        o = createObject(OBJ_STRING,res);
        setKey(c->db,targetkey,o);
        notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"set",targetkey,c->db->id);
        decrRefCount(o);
