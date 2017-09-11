        addReply(c,shared.czero);
        return;
    }

    /* Remove the src set from the database when empty */
    if (setTypeSize(srcset) == 0) dbDelete(c->db,c->argv[1]);
    signalModifiedKey(c->db,c->argv[1]);
    signalModifiedKey(c->db,c->argv[2]);
    server.dirty++;
