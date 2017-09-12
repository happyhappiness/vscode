                stopAppendOnly();
            } else {
                if (startAppendOnly() == REDIS_ERR) {
                    addReplySds(c,sdscatprintf(sdsempty(),
                        "-ERR Unable to turn on AOF. Check server logs.\r\n"));
                    decrRefCount(o);
                    return;
                }
