            incrRefCount(value);
            addReply(c,shared.ok);
            signalModifiedKey(c->db,c->argv[1]);
            server.dirty++;
        }
    } else {
