                addReplyError(c,"Multi keys request invalid in cluster");
                return REDIS_OK;
            } else if (n != server.cluster->myself) {
                addReplySds(c,sdscatprintf(sdsempty(),
                    "-%s %d %s:%d\r\n", ask ? "ASK" : "MOVED",
                    hashslot,n->ip,n->port));
