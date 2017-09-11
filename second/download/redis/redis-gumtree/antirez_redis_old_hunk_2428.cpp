
        /* Update config if needed */
        if (update_config) clusterSaveConfigOrDie();
    } else if (type == CLUSTERMSG_TYPE_PONG) {
        int update_state = 0;
        int update_config = 0;

        redisLog(REDIS_DEBUG,"Pong packet received: %p", (void*)link->node);
        if (link->node) {
            if (link->node->flags & REDIS_NODE_HANDSHAKE) {
                /* If we already have this node, try to change the
