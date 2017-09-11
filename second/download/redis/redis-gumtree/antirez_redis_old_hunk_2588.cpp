
    if (dbDelete(c->db,dstkey)) {
        signalModifiedKey(c->db,dstkey);
        touched = 1;
        server.dirty++;
    }
