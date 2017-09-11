                if (sender) {
                    redisLog(REDIS_WARNING,
                        "Handshake error: we already know node %.40s, updating the address if needed.", sender->name);
                    nodeUpdateAddress(sender,link,ntohs(hdr->port));
                    freeClusterNode(link->node); /* will free the link too */
                    return 0;
                }

