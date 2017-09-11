
                    propagateExpire(db,keyobj);
                    dbDelete(db,keyobj);
                    notifyKeyspaceEvent(REDIS_NOTIFY_EXPIRED,
                        "expired",keyobj,db->id);
                    decrRefCount(keyobj);
                    expired++;
                    server.stat_expiredkeys++;
