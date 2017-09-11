            addReplyBulkCString(c,ni);
            sdsfree(ni);
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"failover") && c->argc == 2) {
        /* CLUSTER FAILOVER */
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
        redisLog(REDIS_WARNING,"Manual failover user request accepted.");
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"set-config-epoch") && c->argc == 3)
