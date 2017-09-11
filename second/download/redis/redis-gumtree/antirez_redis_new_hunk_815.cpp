                /* First thing to do is replacing the random name with the
                 * right node name if this was a handshake stage. */
                clusterRenameNode(link->node, hdr->sender);
                serverLog(LL_DEBUG,"Handshake with node %.40s completed.",
                    link->node->name);
                link->node->flags &= ~REDIS_NODE_HANDSHAKE;
                link->node->flags |= flags&(REDIS_NODE_MASTER|REDIS_NODE_SLAVE);
