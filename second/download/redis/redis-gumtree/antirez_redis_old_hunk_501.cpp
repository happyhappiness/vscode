                if (node->ping_sent == 0) node->ping_sent = mstime();
                serverLog(LL_DEBUG, "Unable to connect to "
                    "Cluster Node [%s]:%d -> %s", node->ip,
                    node->port+CLUSTER_PORT_INCR,
                    server.neterr);
                continue;
            }
            link = createClusterLink(node);
