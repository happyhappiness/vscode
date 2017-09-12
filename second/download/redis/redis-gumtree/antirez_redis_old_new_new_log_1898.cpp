ci = sdscatprintf(ci,"%ld %ld %llu %s",
            (long) node->ping_sent,
            (long) node->pong_received,
            (unsigned long long) node->configEpoch,
            (node->link || node->flags & REDIS_NODE_MYSELF) ?
                        "connected" : "disconnected");