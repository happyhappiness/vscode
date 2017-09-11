    clusterSaveConfigOrDie(1);
    redisLog(REDIS_VERBOSE,
        "WARNING: configEpoch collision with node %.40s."
        " Updating my configEpoch to %llu",
        sender->name,
        (unsigned long long) myself->configEpoch);
}
