        int hashslot;

        if (server.cluster->state != REDIS_CLUSTER_OK) {
            addReplySds(c,sdsnew("-CLUSTERDOWN The cluster is down. Use CLUSTER INFO for more information\r\n"));
            return REDIS_OK;
        } else {
            int ask;
