            } else {
                if (listTypeLength(o) != 0) {
                    /* Non empty list, this is like a non normal [LR]POP. */
                    robj *value = listTypePop(o,where);
                    redisAssert(value != NULL);

                    addReplyMultiBulkLen(c,2);
                    addReplyBulk(c,c->argv[j]);
                    addReplyBulk(c,value);
                    decrRefCount(value);
                    if (listTypeLength(o) == 0) dbDelete(c->db,c->argv[j]);
                    signalModifiedKey(c->db,c->argv[j]);
                    server.dirty++;

