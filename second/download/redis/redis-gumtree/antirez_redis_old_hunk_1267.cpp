    /* Step 4: perform the migration if there is a target, and if I'm the
     * candidate. */
    if (target && candidate == myself) {
        redisLog(REDIS_WARNING,"Migrating to orphaned master %.40s",
            target->name);
        clusterSetMaster(target);
    }
