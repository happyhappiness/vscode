        int hashslot;

        if (server.cluster->state != REDIS_CLUSTER_OK) {
            addReplyError(c,"The cluster is down. Check with CLUSTER INFO for more information");
            return REDIS_OK;
        } else {
            int ask;
