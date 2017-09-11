                    addReplyBulk(c,c->argv[j]);
                    addReplyBulk(c,value);
                    decrRefCount(value);
                    notifyKeyspaceEvent(event,c->argv[j],c->db->id);
                    if (listTypeLength(o) == 0) {
                        dbDelete(c->db,c->argv[j]);
                        notifyKeyspaceEvent("del",c->argv[j],c->db->id);
                    }
                    signalModifiedKey(c->db,c->argv[j]);
                    server.dirty++;
