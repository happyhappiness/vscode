        clusterProcessGossipSection(hdr,link);

        /* Update the cluster state if needed */
        if (update) {
            clusterUpdateState();
            clusterSaveConfigOrDie();
        }
    } else if (type == CLUSTERMSG_TYPE_FAIL && sender) {
        clusterNode *failing;

