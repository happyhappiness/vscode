    }
    if (saveconf) clusterSaveConfigOrDie();
    /* We need a listening TCP port for our cluster messaging needs */
    server.cfd = anetTcpServer(server.neterr,
            server.port+REDIS_CLUSTER_PORT_INCR, server.bindaddr);
    if (server.cfd == -1) {
        redisLog(REDIS_WARNING, "Opening cluster TCP port: %s", server.neterr);
        exit(1);
    }
    if (aeCreateFileEvent(server.el, server.cfd, AE_READABLE,
        clusterAcceptHandler, NULL) == AE_ERR) redisPanic("Unrecoverable error creating Redis Cluster file event.");
    server.cluster->slots_to_keys = zslCreate();
}

