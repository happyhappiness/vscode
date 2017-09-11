        clusterAddNode(server.cluster->myself);
        saveconf = 1;
    }
    if (saveconf) clusterSaveConfigOrDie();

    /* We need a listening TCP port for our cluster messaging needs. */
    server.cfd_count = 0;
