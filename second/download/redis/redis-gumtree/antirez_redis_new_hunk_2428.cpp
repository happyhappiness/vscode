
        /* Update config if needed */
        if (update_config) clusterSaveConfigOrDie();
    }

    /* PING or PONG: process config information. */
    if (type == CLUSTERMSG_TYPE_PING || type == CLUSTERMSG_TYPE_PONG) {
        int update_state = 0;
        int update_config = 0;

        redisLog(REDIS_DEBUG,"%s packet received: %p",
            type == CLUSTERMSG_TYPE_PING ? "ping" : "pong",
            (void*)link->node);
        if (link->node) {
            if (link->node->flags & REDIS_NODE_HANDSHAKE) {
                /* If we already have this node, try to change the
