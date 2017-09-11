                    server.cluster->lastVoteEpoch =
                            strtoull(argv[j+1],NULL,10);
                } else {
                    serverLog(REDIS_WARNING,
                        "Skipping unknown cluster config variable '%s'",
                        argv[j]);
                }
