            sdsfree(ni);
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"failover") && c->argc == 2) {
        /* CLUSTER FAILOVER */
        if (nodeIsMaster(myself)) {
            addReplyError(c,"You should send CLUSTER FAILOVER to a slave");
            return;
