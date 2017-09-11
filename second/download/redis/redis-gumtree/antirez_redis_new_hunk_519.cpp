        sdsfree(oldname);
        getRandomHexChars(myself->name, CLUSTER_NAMELEN);
        clusterAddNode(myself);
        serverLog(LL_NOTICE,"Node hard reset, now I'm %.40s", myself->name);
    }

    /* Make sure to persist the new config and update the state. */
