notifyKeyspaceEvent(REDIS_NOTIFY_LIST,event,
                                        c->argv[j],c->db->id);