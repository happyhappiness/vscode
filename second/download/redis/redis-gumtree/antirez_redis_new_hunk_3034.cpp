        ci = sdscatprintf(ci,"%ld %ld %s",
            (long) node->ping_sent,
            (long) node->pong_received,
            (node->link || node->flags & REDIS_NODE_MYSELF) ?
                        "connected" : "disconnected");

        /* Slots served by this instance */
        start = -1;
