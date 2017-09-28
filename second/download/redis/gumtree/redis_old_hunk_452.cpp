    /* Step 4: perform the migration if there is a target, and if I'm the
     * candidate, but only if the master is continuously orphaned for a
     * couple of seconds, so that during failovers, we give some time to
     * the natural slaves of this instance to advertise their switch from
     * the old master to the new one. */
    if (target && candidate == myself &&
        (mstime()-target->orphaned_time) > REDIS_CLUSTER_SLAVE_MIGRATION_DELAY)
    {
        redisLog(REDIS_WARNING,"Migrating to orphaned master %.40s",
            target->name);
        clusterSetMaster(target);
    }
}

/* -----------------------------------------------------------------------------
