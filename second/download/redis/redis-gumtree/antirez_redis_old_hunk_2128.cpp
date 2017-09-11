            addReplySds(c,sdsnew("-CLUSTERDOWN The cluster is down. Use CLUSTER INFO for more information\r\n"));
            return REDIS_OK;
        } else {
            int ask;
            clusterNode *n = getNodeByQuery(c,c->cmd,c->argv,c->argc,&hashslot,&ask);
            if (n == NULL) {
                addReplyError(c,"Multi keys request invalid in cluster");
                return REDIS_OK;
            } else if (n != server.cluster->myself) {
                flagTransaction(c);
                addReplySds(c,sdscatprintf(sdsempty(),
                    "-%s %d %s:%d\r\n", ask ? "ASK" : "MOVED",
                    hashslot,n->ip,n->port));
                return REDIS_OK;
            }
