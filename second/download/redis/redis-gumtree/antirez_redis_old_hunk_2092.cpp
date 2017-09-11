    /* Don't act if the colliding node has a smaller Node ID. */
    if (memcmp(sender->name,myself->name,REDIS_CLUSTER_NAMELEN) <= 0) return;
    /* Get the next ID available at the best of this node knowledge. */
    myself->configEpoch = clusterGetMaxEpoch()+1;
    clusterSaveConfigOrDie(1);
    redisLog(REDIS_VERBOSE,
        "WARNING: configEpoch collision with node %.40s."
        "Updating my configEpoch to %llu",
        sender->name,
        (unsigned long long) myself->configEpoch);
}
