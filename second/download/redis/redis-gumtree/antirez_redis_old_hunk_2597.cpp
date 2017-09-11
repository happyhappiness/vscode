    else
        dbAdd(c->db,c->argv[1],new);
    signalModifiedKey(c->db,c->argv[1]);
    server.dirty++;
    addReplyBulk(c,new);

