            addReplyBulkCString(c,ni);
            sdsfree(ni);
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"failover") && c->argc == 2) {
        if (nodeIsMaster(myself)) {
            addReplyError(c,"You should send CLUSTER FAILOVER to a slave");
            return;
        } else if (myself->slaveof == NULL || nodeFailed(myself->slaveof) ||
                   myself->slaveof->link == NULL)
        {
            addReplyError(c,"Master is down or failed, "
                            "please use CLUSTER FAILOVER FORCE");
            return;
        }
        resetManualFailover();
        server.cluster->mf_end = mstime() + REDIS_CLUSTER_MF_TIMEOUT;
        clusterSendMFStart(myself->slaveof);
    } else {
        addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");
    }
