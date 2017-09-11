                if (newmaster && curmaster->numslots == 0) {
                    redisLog(REDIS_WARNING,"Configuration change detected. Reconfiguring myself as a replica of %.40s", sender->name);
                    clusterSetMaster(sender);
                }
            }
        }

        /* Get info from the gossip section */
        clusterProcessGossipSection(hdr,link);

        /* Update the cluster state if needed */
        if (update_state) clusterUpdateState();
        if (update_config) clusterSaveConfigOrDie();
    } else if (type == CLUSTERMSG_TYPE_FAIL) {
        clusterNode *failing;

