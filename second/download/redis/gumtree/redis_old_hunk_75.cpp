                    }
                }
            }
        }
        if (outputlen) {
            setKey(c->db,storekey,sobj);
            server.dirty += outputlen;
        } else if (dbDelete(c->db,storekey)) {
            signalModifiedKey(c->db,storekey);
            server.dirty++;
        }
        decrRefCount(sobj);
        addReplyLongLong(c,outputlen);
    }

