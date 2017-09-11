            (REDIS_NODE_MYSELF|REDIS_NODE_NOADDR|REDIS_NODE_HANDSHAKE))
                continue;

        /* If our ping is older than half the cluster timeout (may happen
         * in a cluster with many nodes), send a new ping. */
        if (node->link &&
            (now - node->ping_sent) > server.cluster_node_timeout/2)
        {
            clusterSendPing(node->link, CLUSTERMSG_TYPE_PING);
            continue;
        }

        /* Check only if we already sent a ping and did not received
         * a reply yet. */
        if (node->ping_sent == 0 ||
            node->ping_sent <= node->pong_received) continue;

        /* If we never received a pong, use the ping time to compute
         * the delay. */
        if (node->pong_received) {
            delay = now - node->pong_received;
        } else {
            delay = now - node->ping_sent;
        }

        if (delay < server.cluster_node_timeout) {
            /* The PFAIL condition can be reversed without external
             * help if it is not transitive (that is, if it does not
             * turn into a FAIL state).
             *
             * The FAIL condition is also reversible under specific
             * conditions detected by clearNodeFailureIfNeeded(). */
            if (node->flags & REDIS_NODE_PFAIL) {
                node->flags &= ~REDIS_NODE_PFAIL;
                update_state = 1;
            } else if (node->flags & REDIS_NODE_FAIL) {
                clearNodeFailureIfNeeded(node);
            }
        } else {
            /* Timeout reached. Set the node as possibly failing if it is
             * not already in this state. */
            if (!(node->flags & (REDIS_NODE_PFAIL|REDIS_NODE_FAIL))) {
