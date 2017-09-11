        sdsfree(oldname);
        getRandomHexChars(myself->name, CLUSTER_NAMELEN);
        clusterAddNode(myself);
    }

    /* Make sure to persist the new config and update the state. */
