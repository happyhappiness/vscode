void clusterInit(void) {
    int saveconf = 0;

    server.cluster.myself = createClusterNode(NULL,REDIS_NODE_MYSELF);
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
        redisLog(REDIS_NOTICE,"No cluster configuration found, I'm %.40s",
            server.cluster.myself->name);
        saveconf = 1;
    }
    clusterAddNode(server.cluster.myself);
    if (saveconf) clusterSaveConfigOrDie();
    /* We need a listening TCP port for our cluster messaging needs */
    server.cfd = anetTcpServer(server.neterr,
            server.port+REDIS_CLUSTER_PORT_INCR, server.bindaddr);
    if (server.cfd == -1) {
        redisLog(REDIS_WARNING, "Opening cluster TCP port: %s", server.neterr);
        exit(1);
    }
    if (aeCreateFileEvent(server.el, server.cfd, AE_READABLE,
        clusterAcceptHandler, NULL) == AE_ERR) oom("creating file event");
}