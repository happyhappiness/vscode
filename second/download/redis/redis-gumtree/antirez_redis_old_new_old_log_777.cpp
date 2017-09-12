serverLog(REDIS_WARNING,
                "Received replication offset for paused "
                "master manual failover: %lld",
                server.cluster->mf_master_offset);