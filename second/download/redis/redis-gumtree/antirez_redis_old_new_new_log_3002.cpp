addReplySds(c,sdscatprintf(sdsempty(),
                    "-MOVED %d %s:%d\r\n",hashslot,n->ip,n->port));