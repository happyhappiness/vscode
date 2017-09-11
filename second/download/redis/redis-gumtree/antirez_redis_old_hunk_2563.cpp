                ziplistLen(subject->ptr) > server.list_max_ziplist_entries)
                    listTypeConvert(subject,REDIS_ENCODING_LINKEDLIST);
            signalModifiedKey(c->db,c->argv[1]);
            server.dirty++;
        } else {
            /* Notify client of a failed insert */
            addReply(c,shared.cnegone);
            return;
        }
    } else {
        listTypePush(subject,val,where);
        signalModifiedKey(c->db,c->argv[1]);
        server.dirty++;
    }

