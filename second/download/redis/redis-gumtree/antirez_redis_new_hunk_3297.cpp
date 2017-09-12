        return REDIS_OK;
    }

    /* If cluster is enabled, redirect here */
    if (server.cluster_enabled &&
                !(cmd->getkeys_proc == NULL && cmd->firstkey == 0)) {
        int hashslot;

        if (server.cluster.state != REDIS_CLUSTER_OK) {
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
    }

    /* Handle the maxmemory directive.
     *
     * First we try to free some memory if possible (if there are volatile
