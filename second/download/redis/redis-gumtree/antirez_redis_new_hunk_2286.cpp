                if (newmaster && curmaster->numslots == 0) {
                    redisLog(REDIS_WARNING,"Configuration change detected. Reconfiguring myself as a replica of %.40s", sender->name);
                    clusterSetMaster(sender);
                    clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                                         CLUSTER_TODO_UPDATE_STATE|
                                         CLUSTER_TODO_FSYNC_CONFIG);
                }
            }
        }

        /* Get info from the gossip section */
        clusterProcessGossipSection(hdr,link);
    } else if (type == CLUSTERMSG_TYPE_FAIL) {
        clusterNode *failing;

