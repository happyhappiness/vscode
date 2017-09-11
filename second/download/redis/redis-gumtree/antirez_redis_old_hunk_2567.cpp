    } else {
        redisPanic("Unknown list encoding");
    }
    if (listTypeLength(o) == 0) dbDelete(c->db,c->argv[1]);
    signalModifiedKey(c->db,c->argv[1]);
    server.dirty++;
    addReply(c,shared.ok);
