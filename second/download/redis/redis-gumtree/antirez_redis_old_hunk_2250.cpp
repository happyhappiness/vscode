                    if (server.cluster->slots[j]->configEpoch >
                        senderConfigEpoch)
                    {
                        printf("MASTER or SLAVE have old config\n");
                        break;
                    }
                }
            }
