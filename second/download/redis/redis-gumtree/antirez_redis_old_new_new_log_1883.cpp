redisLog(REDIS_WARNING,
                            "Node %.40s has old slots configuration, sending "
                            "an UPDATE message about %.40s\n",
                                sender->name, server.cluster->slots[j]->name);