                    if (server.cluster->slots[j]->configEpoch >
                        senderConfigEpoch)
                    {
                        redisLog(REDIS_WARNING,
                            "Node %.40s has old slots configuration, sending "
                            "an UPDATE message about %.40s\n",
                                sender->name, server.cluster->slots[j]->name);
                        clusterSendUpdate(sender->link,server.cluster->slots[j]);
                    }
                }
            }
