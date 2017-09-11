
    if (dbDelete(c->db,dstkey)) {
        signalModifiedKey(c->db,dstkey);
        notifyKeyspaceEvent("del",dstkey,c->db->id);
        touched = 1;
        server.dirty++;
    }
