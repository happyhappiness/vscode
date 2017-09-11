
                    propagateExpire(db,keyobj);
                    dbDelete(db,keyobj);
                    notifyKeyspaceEvent("expired",keyobj,db->id);
                    decrRefCount(keyobj);
                    expired++;
                    server.stat_expiredkeys++;
