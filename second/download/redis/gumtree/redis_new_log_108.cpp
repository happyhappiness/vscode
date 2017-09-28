notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",
                                            c->argv[j],c->db->id);