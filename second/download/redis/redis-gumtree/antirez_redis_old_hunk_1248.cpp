                    if (server.cluster->slots[j]->configEpoch >
                        senderConfigEpoch)
                    {
                        redisLog(REDIS_VERBOSE,
                            "Node %.40s has old slots configuration, sending "
                            "an UPDATE message about %.40s",
                                sender->name, server.cluster->slots[j]->name);
