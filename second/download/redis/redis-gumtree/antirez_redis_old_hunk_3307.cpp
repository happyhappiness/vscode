        sizeof(server.cluster.importing_slots_from));
    memset(server.cluster.slots,0,
        sizeof(server.cluster.slots));
    if (clusterLoadConfig("redis-cluster.conf") == REDIS_ERR) {
        /* No configuration found. We will just use the random name provided
         * by the createClusterNode() function. */
        redisLog(REDIS_NOTICE,"No cluster configuration found, I'm %.40s",
            server.cluster.myself->name);
        saveconf = 1;
    }
    clusterAddNode(server.cluster.myself);
    if (saveconf) {
        if (clusterSaveConfig("redis-cluster.conf") == -1) {
            redisLog(REDIS_WARNING,"Fatal: can't update cluster config file.");
            exit(1);
        }
    }
    /* We need a listening TCP port for our cluster messaging needs */
    server.cfd = anetTcpServer(server.neterr,
            server.port+REDIS_CLUSTER_PORT_INCR, server.bindaddr);
