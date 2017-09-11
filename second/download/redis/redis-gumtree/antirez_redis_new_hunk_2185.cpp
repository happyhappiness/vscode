        clusterSetMaster(n);
        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"slaves") && c->argc == 3) {
        /* CLUSTER SLAVES <NODE ID> */
        clusterNode *n = clusterLookupNode(c->argv[2]->ptr);
        int j;

        /* Lookup the specified node in our table. */
        if (!n) {
            addReplyErrorFormat(c,"Unknown node %s", (char*)c->argv[2]->ptr);
            return;
        }

        if (n->flags & REDIS_NODE_SLAVE) {
            addReplyError(c,"The specified node is not a master");
            return;
        }

        addReplyMultiBulkLen(c,n->numslaves);
        for (j = 0; j < n->numslaves; j++) {
            sds ni = clusterGenNodeDescription(n->slaves[j]);
            addReplyBulkCString(c,ni);
            sdsfree(ni);
        }
    } else {
        addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");
    }
