    for (j = 1; j < c->argc; j++) {
        if (dbDelete(c->db,c->argv[j])) {
            signalModifiedKey(c->db,c->argv[j]);
            server.dirty++;
            deleted++;
        }
