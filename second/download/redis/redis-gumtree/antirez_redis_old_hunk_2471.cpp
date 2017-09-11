void clusterInit(void) {
    int saveconf = 0;

    server.cluster.myself = NULL;
    server.cluster.state = REDIS_CLUSTER_FAIL;
    server.cluster.nodes = dictCreate(&clusterNodesDictType,NULL);
    server.cluster.node_timeout = 15;
    memset(server.cluster.migrating_slots_to,0,
        sizeof(server.cluster.migrating_slots_to));
    memset(server.cluster.importing_slots_from,0,
        sizeof(server.cluster.importing_slots_from));
    memset(server.cluster.slots,0,
        sizeof(server.cluster.slots));
    if (clusterLoadConfig(server.cluster.configfile) == REDIS_ERR) {
        /* No configuration found. We will just use the random name provided
         * by the createClusterNode() function. */
        server.cluster.myself = createClusterNode(NULL,REDIS_NODE_MYSELF);
        redisLog(REDIS_NOTICE,"No cluster configuration found, I'm %.40s",
            server.cluster.myself->name);
        clusterAddNode(server.cluster.myself);
        saveconf = 1;
    }
    if (saveconf) clusterSaveConfigOrDie();
