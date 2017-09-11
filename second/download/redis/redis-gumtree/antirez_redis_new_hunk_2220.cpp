            ci = sdscatprintf(ci,"- ");

        /* Latency from the POV of this node, link status */
        ci = sdscatprintf(ci,"%lld %lld %llu %s",
            (long long) node->ping_sent,
            (long long) node->pong_received,
            (unsigned long long) node->configEpoch,
            (node->link || node->flags & REDIS_NODE_MYSELF) ?
                        "connected" : "disconnected");
