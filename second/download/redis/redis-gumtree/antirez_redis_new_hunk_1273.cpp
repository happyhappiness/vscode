            /* Timeout reached. Set the node as possibly failing if it is
             * not already in this state. */
            if (!(node->flags & (REDIS_NODE_PFAIL|REDIS_NODE_FAIL))) {
                serverLog(REDIS_DEBUG,"*** NODE %.40s possibly failing",
                    node->name);
                node->flags |= REDIS_NODE_PFAIL;
                update_state = 1;
