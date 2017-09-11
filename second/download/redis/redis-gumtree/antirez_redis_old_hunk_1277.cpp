             * generates a new configuration epoch for this node without
             * consensus, claims the master's slots, and broadcast the new
             * configuration. */
            redisLog(REDIS_WARNING,"Taking over the master (user request).");
            clusterBumpConfigEpochWithoutConsensus();
            clusterFailoverReplaceYourMaster();
        } else if (force) {
            /* If this is a forced failover, we don't need to talk with our
             * master to agree about the offset. We just failover taking over
             * it without coordination. */
            redisLog(REDIS_WARNING,"Forced failover user request accepted.");
            server.cluster->mf_can_start = 1;
        } else {
            redisLog(REDIS_WARNING,"Manual failover user request accepted.");
            clusterSendMFStart(myself->slaveof);
        }
        addReply(c,shared.ok);
