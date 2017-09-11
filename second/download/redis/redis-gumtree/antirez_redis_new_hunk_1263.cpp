            server.cluster->failover_auth_time = mstime();
            server.cluster->failover_auth_rank = 0;
        }
        serverLog(REDIS_WARNING,
            "Start of election delayed for %lld milliseconds "
            "(rank #%d, offset %lld).",
            server.cluster->failover_auth_time - mstime(),
