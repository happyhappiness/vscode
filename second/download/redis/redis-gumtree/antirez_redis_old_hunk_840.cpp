             * normal PING packets. */
            node->flags &= ~REDIS_NODE_MEET;

            serverLog(REDIS_DEBUG,"Connecting with Node %.40s at %s:%d",
                    node->name, node->ip, node->port+REDIS_CLUSTER_PORT_INCR);
        }
    }
