                (newrank - server.cluster->failover_auth_rank) * 1000;
            server.cluster->failover_auth_time += added_delay;
            server.cluster->failover_auth_rank = newrank;
            serverLog(LL_WARNING,
                "Slave rank updated to #%d, added %lld milliseconds of delay.",
                newrank, added_delay);
        }
