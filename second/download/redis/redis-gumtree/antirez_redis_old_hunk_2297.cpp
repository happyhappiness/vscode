        /* Update the cluster state if needed */
        if (update_state) clusterUpdateState();
        if (update_config) clusterSaveConfigOrDie();
    } else if (type == CLUSTERMSG_TYPE_FAIL && sender) {
        clusterNode *failing;

        failing = clusterLookupNode(hdr->data.fail.about.nodename);
        if (failing && !(failing->flags & (REDIS_NODE_FAIL|REDIS_NODE_MYSELF)))
        {
            redisLog(REDIS_NOTICE,
                "FAIL message received from %.40s about %.40s",
                hdr->sender, hdr->data.fail.about.nodename);
            failing->flags |= REDIS_NODE_FAIL;
            failing->fail_time = time(NULL);
            failing->flags &= ~REDIS_NODE_PFAIL;
            clusterUpdateState();
            clusterSaveConfigOrDie();
        }
    } else if (type == CLUSTERMSG_TYPE_PUBLISH) {
        robj *channel, *message;
