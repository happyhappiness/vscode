         * by the createClusterNode() function. */
        redisLog(REDIS_NOTICE,"No cluster configuration found, I'm %.40s",
            server.cluster.myself->name);
        clusterAddNode(server.cluster.myself);
        saveconf = 1;
    }
    if (saveconf) clusterSaveConfigOrDie();
    /* We need a listening TCP port for our cluster messaging needs */
    server.cfd = anetTcpServer(server.neterr,
