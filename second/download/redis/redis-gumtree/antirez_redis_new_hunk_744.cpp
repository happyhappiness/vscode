            /* We already know this node.
               Handle failure reports, only when the sender is a master. */
            if (sender && nodeIsMaster(sender) && node != myself) {
                if (flags & (CLUSTER_NODE_FAIL|CLUSTER_NODE_PFAIL)) {
                    if (clusterNodeAddFailureReport(node,sender)) {
                        serverLog(LL_VERBOSE,
                            "Node %.40s reported node %.40s as not reachable.",
