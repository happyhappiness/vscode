addReplySds(c,sdscatprintf(sdsempty(),
                    "-%s %d %s:%d\r\n",
                    (error_code == REDIS_CLUSTER_REDIR_ASK) ? "ASK" : "MOVED",
                    hashslot,n->ip,n->port));