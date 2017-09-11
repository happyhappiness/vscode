            decrRefCount(value);
            addReply(c,shared.ok);
            signalModifiedKey(c->db,c->argv[1]);
            server.dirty++;
        }
    } else if (o->encoding == REDIS_ENCODING_LINKEDLIST) {
