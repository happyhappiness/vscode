        }

        /* Set the master. */
        server.cluster->myself->flags &= ~REDIS_NODE_PROMOTED;
        clusterSetMaster(n);
        clusterUpdateState();
        clusterSaveConfigOrDie();
