        } else {
            goto badfmt;
        }
    } else if (!strcasecmp(c->argv[2]->ptr,"appendonly")) {
        int old = server.appendonly;
        int new = yesnotoi(o->ptr);

        if (new == -1) goto badfmt;
        if (old != new) {
            if (new == 0) {
                stopAppendOnly();
            } else {
                if (startAppendOnly() == REDIS_ERR) {
                    addReplySds(c,sdscatprintf(sdsempty(),
                        "-ERR Unable to turn on AOF. Check server logs.\r\n"));
                    decrRefCount(o);
                    return;
                }
            }
        }
    } else if (!strcasecmp(c->argv[2]->ptr,"save")) {
        int vlen, j;
        sds *v = sdssplitlen(o->ptr,sdslen(o->ptr)," ",1,&vlen);
