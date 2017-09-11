                 redisLog(REDIS_DEBUG,"Node pong_received updated by gossip");
                node->pong_received = ntohl(g->pong_received);
            }
            /* Mark this node as FAILED if we think it is possibly failing
             * and another node also thinks it's failing. */
            if (node->flags & REDIS_NODE_PFAIL &&
                (flags & (REDIS_NODE_FAIL|REDIS_NODE_PFAIL)))
            {
                redisLog(REDIS_NOTICE,"Received a PFAIL acknowledge from node %.40s, marking node %.40s as FAIL!", hdr->sender, node->name);
                node->flags &= ~REDIS_NODE_PFAIL;
                node->flags |= REDIS_NODE_FAIL;
                /* Broadcast the failing node name to everybody */
                clusterSendFail(node->name);
                clusterUpdateState();
                clusterSaveConfigOrDie();
            }
        } else {
            /* If it's not in NOADDR state and we don't have it, we
