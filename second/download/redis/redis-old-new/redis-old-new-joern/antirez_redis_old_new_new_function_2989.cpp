int clusterProcessPacket(clusterLink *link) {
    clusterMsg *hdr = (clusterMsg*) link->rcvbuf;
    uint32_t totlen = ntohl(hdr->totlen);
    uint16_t type = ntohs(hdr->type);
    clusterNode *sender;

    redisLog(REDIS_DEBUG,"--- packet to process %lu bytes (%lu) ---",
        (unsigned long) totlen, sdslen(link->rcvbuf));
    if (totlen < 8) return 1;
    if (totlen > sdslen(link->rcvbuf)) return 1;
    if (type == CLUSTERMSG_TYPE_PING || type == CLUSTERMSG_TYPE_PONG ||
        type == CLUSTERMSG_TYPE_MEET)
    {
        uint16_t count = ntohs(hdr->count);
        uint32_t explen; /* expected length of this packet */

        explen = sizeof(clusterMsg)-sizeof(union clusterMsgData);
        explen += (sizeof(clusterMsgDataGossip)*count);
        if (totlen != explen) return 1;
    }
    if (type == CLUSTERMSG_TYPE_FAIL) {
        uint32_t explen = sizeof(clusterMsg)-sizeof(union clusterMsgData);

        explen += sizeof(clusterMsgDataFail);
        if (totlen != explen) return 1;
    }

    sender = clusterLookupNode(hdr->sender);
    if (type == CLUSTERMSG_TYPE_PING || type == CLUSTERMSG_TYPE_MEET) {
        int update_config = 0;
        redisLog(REDIS_DEBUG,"Ping packet received: %p", link->node);

        /* Add this node if it is new for us and the msg type is MEET.
         * In this stage we don't try to add the node with the right
         * flags, slaveof pointer, and so forth, as this details will be
         * resolved when we'll receive PONGs from the server. */
        if (!sender && type == CLUSTERMSG_TYPE_MEET) {
            clusterNode *node;

            node = createClusterNode(NULL,REDIS_NODE_HANDSHAKE);
            nodeIp2String(node->ip,link);
            node->port = ntohs(hdr->port);
            clusterAddNode(node);
            update_config = 1;
        }

        /* Get info from the gossip section */
        clusterProcessGossipSection(hdr,link);

        /* Anyway reply with a PONG */
        clusterSendPing(link,CLUSTERMSG_TYPE_PONG);

        /* Update config if needed */
        if (update_config) clusterSaveConfigOrDie();
    } else if (type == CLUSTERMSG_TYPE_PONG) {
        int update_state = 0;
        int update_config = 0;

        redisLog(REDIS_DEBUG,"Pong packet received: %p", link->node);
        if (link->node) {
            if (link->node->flags & REDIS_NODE_HANDSHAKE) {
                /* If we already have this node, try to change the
                 * IP/port of the node with the new one. */
                if (sender) {
                    redisLog(REDIS_WARNING,
                        "Handshake error: we already know node %.40s, updating the address if needed.", sender->name);
                    nodeUpdateAddress(sender,link,ntohs(hdr->port));
                    freeClusterNode(link->node); /* will free the link too */
                    return 0;
                }

                /* First thing to do is replacing the random name with the
                 * right node name if this was an handshake stage. */
                clusterRenameNode(link->node, hdr->sender);
                redisLog(REDIS_DEBUG,"Handshake with node %.40s completed.",
                    link->node->name);
                link->node->flags &= ~REDIS_NODE_HANDSHAKE;
                update_config = 1;
            } else if (memcmp(link->node->name,hdr->sender,
                        REDIS_CLUSTER_NAMELEN) != 0)
            {
                /* If the reply has a non matching node ID we
                 * disconnect this node and set it as not having an associated
                 * address. */
                redisLog(REDIS_DEBUG,"PONG contains mismatching sender ID");
                link->node->flags |= REDIS_NODE_NOADDR;
                freeClusterLink(link);
                update_config = 1;
                /* FIXME: remove this node if we already have it.
                 *
                 * If we already have it but the IP is different, use
                 * the new one if the old node is in FAIL, PFAIL, or NOADDR
                 * status... */
                return 0;
            }
        }
        /* Update our info about the node */
        link->node->pong_received = time(NULL);

        /* Update master/slave info */
        if (sender) {
            if (!memcmp(hdr->slaveof,REDIS_NODE_NULL_NAME,
                sizeof(hdr->slaveof)))
            {
                sender->flags &= ~REDIS_NODE_SLAVE;
                sender->flags |= REDIS_NODE_MASTER;
                sender->slaveof = NULL;
            } else {
                clusterNode *master = clusterLookupNode(hdr->slaveof);

                sender->flags &= ~REDIS_NODE_MASTER;
                sender->flags |= REDIS_NODE_SLAVE;
                if (sender->numslaves) clusterNodeResetSlaves(sender);
                if (master) clusterNodeAddSlave(master,sender);
            }
        }

        /* Update our info about served slots if this new node is serving
         * slots that are not served from our point of view. */
        if (sender && sender->flags & REDIS_NODE_MASTER) {
            int newslots, j;

            newslots =
                memcmp(sender->slots,hdr->myslots,sizeof(hdr->myslots)) != 0;
            memcpy(sender->slots,hdr->myslots,sizeof(hdr->myslots));
            if (newslots) {
                for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
                    if (clusterNodeGetSlotBit(sender,j)) {
                        if (server.cluster.slots[j] == sender) continue;
                        if (server.cluster.slots[j] == NULL ||
                            server.cluster.slots[j]->flags & REDIS_NODE_FAIL)
                        {
                            server.cluster.slots[j] = sender;
                            update_state = update_config = 1;
                        }
                    }
                }
            }
        }

        /* Get info from the gossip section */
        clusterProcessGossipSection(hdr,link);

        /* Update the cluster state if needed */
        if (update_state) clusterUpdateState();
        if (update_config) clusterSaveConfigOrDie();
    } else if (type == CLUSTERMSG_TYPE_FAIL && sender) {
        clusterNode *failing;

        failing = clusterLookupNode(hdr->data.fail.about.nodename);
        if (failing && !(failing->flags & REDIS_NODE_FAIL)) {
            redisLog(REDIS_NOTICE,
                "FAIL message received from %.40s about %.40s",
                hdr->sender, hdr->data.fail.about.nodename);
            failing->flags |= REDIS_NODE_FAIL;
            failing->flags &= ~REDIS_NODE_PFAIL;
            clusterUpdateState();
            clusterSaveConfigOrDie();
        }
    } else {
        redisLog(REDIS_NOTICE,"Received unknown packet type: %d", type);
    }
    return 1;
}