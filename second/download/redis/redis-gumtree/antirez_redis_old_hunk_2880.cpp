
            /* Finally remove the selected key. */
            if (bestkey) {
                robj *keyobj = createStringObject(bestkey,sdslen(bestkey));
                propagateExpire(db,keyobj);
                dbDelete(db,keyobj);
                server.stat_evictedkeys++;
                decrRefCount(keyobj);
                freed++;
            }
        }
        if (!freed) return; /* nothing to free... */
    }
}

/* =================================== Main! ================================ */
