            clusterLink *link;

            fd = anetTcpNonBlockBindConnect(server.neterr, node->ip,
                node->port+REDIS_CLUSTER_PORT_INCR, NET_FIRST_BIND_ADDR);
            if (fd == -1) {
                /* We got a synchronous error from connect before
                 * clusterSendPing() had a chance to be called.
                 * If node->ping_sent is zero, failure detection can't work,
                 * so we claim we actually sent a ping now (that will
                 * be really sent as soon as the link is obtained). */
                if (node->ping_sent == 0) node->ping_sent = mstime();
                serverLog(LL_DEBUG, "Unable to connect to "
                    "Cluster Node [%s]:%d -> %s", node->ip,
                    node->port+REDIS_CLUSTER_PORT_INCR,
                    server.neterr);
