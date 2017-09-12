                stopAppendOnly();
            } else {
                if (startAppendOnly() == REDIS_ERR) {
                    addReplyError(c,
                        "Unable to turn on AOF. Check server logs.");
                    decrRefCount(o);
                    return;
                }
