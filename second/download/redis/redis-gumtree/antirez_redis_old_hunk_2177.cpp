        myself = server.cluster->myself =
            createClusterNode(NULL,REDIS_NODE_MYSELF|REDIS_NODE_MASTER);
        redisLog(REDIS_NOTICE,"No cluster configuration found, I'm %.40s",
            server.cluster->myself->name);
        clusterAddNode(server.cluster->myself);
        saveconf = 1;
    }
    if (saveconf) clusterSaveConfigOrDie(1);
