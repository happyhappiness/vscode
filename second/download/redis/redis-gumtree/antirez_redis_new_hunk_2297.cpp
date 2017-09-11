        /* Update the cluster state if needed */
        if (update_state) clusterUpdateState();
        if (update_config) clusterSaveConfigOrDie();
    } else if (type == CLUSTERMSG_TYPE_FAIL) {
        clusterNode *failing;

        if (sender) {
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
        } else {
            redisLog(REDIS_NOTICE,
                "Ignoring FAIL message from unknonw node %.40s about %.40s",
                hdr->sender, hdr->data.fail.about.nodename);
        }
    } else if (type == CLUSTERMSG_TYPE_PUBLISH) {
        robj *channel, *message;
