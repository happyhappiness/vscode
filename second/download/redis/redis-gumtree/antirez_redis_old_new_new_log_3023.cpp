ci = sdscatprintf(ci,"%ld %ld %s\n",
            (long) node->ping_sent,
            (long) node->pong_received,
            node->link ? "connected" : "disconnected");