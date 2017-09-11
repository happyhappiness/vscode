            if (sender && nodeIsMaster(sender) && node != myself) {
                if (flags & (REDIS_NODE_FAIL|REDIS_NODE_PFAIL)) {
                    if (clusterNodeAddFailureReport(node,sender)) {
                        redisLog(REDIS_VERBOSE,
                            "Node %.40s reported node %.40s as not reachable.",
                            sender->name, node->name);
                    }
                    markNodeAsFailingIfNeeded(node);
                } else {
                    if (clusterNodeDelFailureReport(node,sender)) {
                        redisLog(REDIS_VERBOSE,
                            "Node %.40s reported node %.40s is back online.",
                            sender->name, node->name);
                    }
