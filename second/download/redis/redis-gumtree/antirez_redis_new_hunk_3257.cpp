            addReplyError(c,"The cluster is down. Check with CLUSTER INFO for more information");
            return REDIS_OK;
        } else {
            int ask;
            clusterNode *n = getNodeByQuery(c,cmd,c->argv,c->argc,&hashslot,&ask);
            if (n == NULL) {
                addReplyError(c,"Multi keys request invalid in cluster");
                return REDIS_OK;
            } else if (n != server.cluster.myself) {
                addReplySds(c,sdscatprintf(sdsempty(),
                    "-%s %d %s:%d\r\n", ask ? "ASK" : "MOVED",
                    hashslot,n->ip,n->port));
                return REDIS_OK;
            }
        }
