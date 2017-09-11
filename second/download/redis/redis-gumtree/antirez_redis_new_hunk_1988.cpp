            addReplyBulkCString(c,ni);
            sdsfree(ni);
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"failover") &&
               (c->argc == 2 || c->argc == 3))
    {
        /* CLUSTER FAILOVER [FORCE] */
        int force = 0;

        if (c->argc == 3) {
            if (!strcasecmp(c->argv[2]->ptr,"force")) {
                force = 1;
            } else {
                addReply(c,shared.syntaxerr);
                return;
            }
        }

        if (nodeIsMaster(myself)) {
            addReplyError(c,"You should send CLUSTER FAILOVER to a slave");
            return;
        } else if (!force &&
                   (myself->slaveof == NULL || nodeFailed(myself->slaveof) ||
                   myself->slaveof->link == NULL))
        {
            addReplyError(c,"Master is down or failed, "
                            "please use CLUSTER FAILOVER FORCE");
            return;
        }
        resetManualFailover();
        server.cluster->mf_end = mstime() + REDIS_CLUSTER_MF_TIMEOUT;

        /* If this is a forced failover, we don't need to talk with our master
         * to agree about the offset. We just failover taking over it without
         * coordination. */
        if (force) {
            server.cluster->mf_can_start = 1;
        } else {
            clusterSendMFStart(myself->slaveof);
        }
        redisLog(REDIS_WARNING,"Manual failover user request accepted.");
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"set-config-epoch") && c->argc == 3)
