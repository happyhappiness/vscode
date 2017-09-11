        /* Our replication offset matches the master replication offset
         * announced after clients were paused. We can start the failover. */
        server.cluster->mf_can_start = 1;
        redisLog(REDIS_WARNING,
            "All master replication stream processed, "
            "manual failover can start.");
    }
