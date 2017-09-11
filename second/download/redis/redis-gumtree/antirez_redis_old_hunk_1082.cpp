                 * failover happens at the same time we close the slot, the
                 * configEpoch collision resolution will fix it assigning
                 * a different epoch to each node. */
                if (clusterBumpConfigEpochWithoutConsensus() == REDIS_OK) {
                    serverLog(REDIS_WARNING,
                        "configEpoch updated after importing slot %d", slot);
                }
