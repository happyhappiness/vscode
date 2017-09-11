                 redisLog(REDIS_DEBUG,"Node pong_received updated by gossip");
                node->pong_received = ntohl(g->pong_received);
            }
            /* Handle failure reports, only when the sender is a master. */
            if (sender && sender->flags & REDIS_NODE_MASTER) {
                if (flags & (REDIS_NODE_FAIL|REDIS_NODE_PFAIL)) {
                    if (clusterNodeAddFailureReport(node,sender)) {
                        redisLog(REDIS_NOTICE,
                            "Node %.40s reported node %.40s as not reachable.",
                            sender->name, node->name);
                    }
                    markNodeAsFailingIfNeeded(node);
                } else {
                    if (clusterNodeDelFailureReport(node,sender)) {
                        redisLog(REDIS_NOTICE,
                            "Node %.40s reported node %.40s is back online.",
                            sender->name, node->name);
                    }
                }
            }
        } else {
            /* If it's not in NOADDR state and we don't have it, we
