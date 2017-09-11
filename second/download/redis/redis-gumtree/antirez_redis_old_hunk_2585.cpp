    }

    if (deleted) {
        signalModifiedKey(c->db,key);
        server.dirty += deleted;
    }
