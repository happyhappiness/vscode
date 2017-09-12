            addReplyError(c,"The cluster is down. Check with CLUSTER INFO for more information");
            return REDIS_OK;
        } else {
            clusterNode *n = getNodeByQuery(c,cmd,c->argv,c->argc,&hashslot);
            if (n == NULL) {
                addReplyError(c,"Invalid cross-node request");
                return REDIS_OK;
            } else if (n != server.cluster.myself) {
                addReplySds(c,sdscatprintf(sdsempty(),
                    "-MOVED %d %s:%d\r\n",hashslot,n->ip,n->port));
                return REDIS_OK;
            }
        }
