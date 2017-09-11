    hashTypeSet(o,c->argv[2],new);
    addReplyBulk(c,new);
    signalModifiedKey(c->db,c->argv[1]);
    server.dirty++;

    /* Always replicate HINCRBYFLOAT as an HSET command with the final value
