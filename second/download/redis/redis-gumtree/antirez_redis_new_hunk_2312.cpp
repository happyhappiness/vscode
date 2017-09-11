        saveconf = 1;
    }
    if (saveconf) clusterSaveConfigOrDie();

    /* We need a listening TCP port for our cluster messaging needs. */
    server.cfd_count = 0;
    if (listenToPort(server.port+REDIS_CLUSTER_PORT_INCR,
        server.cfd,&server.cfd_count) == REDIS_ERR)
    {
        exit(1);
    }

    /* The slots -> keys map is a sorted set. Init it. */
    server.cluster->slots_to_keys = zslCreate();
}

