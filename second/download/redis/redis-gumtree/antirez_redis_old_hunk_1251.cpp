        server.cluster->mf_end = mstime() + REDIS_CLUSTER_MF_TIMEOUT;
        server.cluster->mf_slave = sender;
        pauseClients(mstime()+(REDIS_CLUSTER_MF_TIMEOUT*2));
        redisLog(REDIS_WARNING,"Manual failover requested by slave %.40s.",
            sender->name);
    } else if (type == CLUSTERMSG_TYPE_UPDATE) {
        clusterNode *n; /* The node the update is about. */
