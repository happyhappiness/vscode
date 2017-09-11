        if (sender) {
            failing = clusterLookupNode(hdr->data.fail.about.nodename);
            if (failing &&
                !(failing->flags & (REDIS_NODE_FAIL|REDIS_NODE_MYSELF)))
            {
                serverLog(LL_NOTICE,
                    "FAIL message received from %.40s about %.40s",
                    hdr->sender, hdr->data.fail.about.nodename);
                failing->flags |= REDIS_NODE_FAIL;
                failing->fail_time = mstime();
                failing->flags &= ~REDIS_NODE_PFAIL;
                clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                                     CLUSTER_TODO_UPDATE_STATE);
            }
