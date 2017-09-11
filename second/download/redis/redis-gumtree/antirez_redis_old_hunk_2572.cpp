            deleted++;
            if (setTypeSize(set) == 0) {
                dbDelete(c->db,c->argv[1]);
                break;
            }
        }
    }
    if (deleted) {
        signalModifiedKey(c->db,c->argv[1]);
        server.dirty += deleted;
    }
    addReplyLongLong(c,deleted);
