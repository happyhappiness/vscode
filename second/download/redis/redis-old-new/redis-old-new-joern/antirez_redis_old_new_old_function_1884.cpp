int clusterProcessPacket(clusterLink *link) {
    clusterMsg *hdr = (clusterMsg*) link->rcvbuf;
    uint32_t totlen = ntohl(hdr->totlen);
    uint16_t type = ntohs(hdr->type);
    uint16_t flags = ntohs(hdr->flags);
    uint64_t senderCurrentEpoch = 0, senderConfigEpoch = 0;
    clusterNode *sender;

    server.cluster->stats_bus_messages_received++;
    redisLog(REDIS_DEBUG,"--- Processing packet of type %d, %lu bytes",
        type, (unsigned long) totlen);

    /* Perform sanity checks */
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
    } else if (type == CLUSTERMSG_TYPE_FAIL) {
        uint32_t explen = sizeof(clusterMsg)-sizeof(union clusterMsgData);

        explen += sizeof(clusterMsgDataFail);
        if (totlen != explen) return 1;
    } else if (type == CLUSTERMSG_TYPE_PUBLISH) {
        uint32_t explen = sizeof(clusterMsg)-sizeof(union clusterMsgData);

        explen += sizeof(clusterMsgDataPublish) +
                ntohl(hdr->data.publish.msg.channel_len) +
                ntohl(hdr->data.publish.msg.message_len);
        if (totlen != explen) return 1;
    } else if (type == CLUSTERMSG_TYPE_FAILOVER_AUTH_REQUEST ||
               type == CLUSTERMSG_TYPE_FAILOVER_AUTH_ACK) {
        uint32_t explen = sizeof(clusterMsg)-sizeof(union clusterMsgData);

        if (totlen != explen) return 1;
    }

    /* Check if the sender is a known node. */
    sender = clusterLookupNode(hdr->sender);
    if (sender && !(sender->flags & REDIS_NODE_HANDSHAKE)) {
        /* Update our curretEpoch if we see a newer epoch in the cluster. */
        senderCurrentEpoch = ntohu64(hdr->currentEpoch);
        senderConfigEpoch = ntohu64(hdr->configEpoch);
        if (senderCurrentEpoch > server.cluster->currentEpoch)
            server.cluster->currentEpoch = senderCurrentEpoch;
        /* Update the sender configEpoch if it is publishing a newer one. */
        if (senderConfigEpoch > sender->configEpoch) {
            sender->configEpoch = senderConfigEpoch;
            clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|CLUSTER_TODO_FSYNC_CONFIG);
        }
    }

    /* Process packets by type. */
    if (type == CLUSTERMSG_TYPE_PING || type == CLUSTERMSG_TYPE_MEET) {
        redisLog(REDIS_DEBUG,"Ping packet received: %p", (void*)link->node);

        /* Add this node if it is new for us and the msg type is MEET.
         * In this stage we don't try to add the node with the right
         * flags, slaveof pointer, and so forth, as this details will be
         * resolved when we'll receive PONGs from the node. */
        if (!sender && type == CLUSTERMSG_TYPE_MEET) {
            clusterNode *node;

            node = createClusterNode(NULL,REDIS_NODE_HANDSHAKE);
            nodeIp2String(node->ip,link);
            node->port = ntohs(hdr->port);
            clusterAddNode(node);
            clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG);
        }

        /* Get info from the gossip section */
        clusterProcessGossipSection(hdr,link);

        /* Anyway reply with a PONG */
        clusterSendPing(link,CLUSTERMSG_TYPE_PONG);
    }

    /* PING or PONG: process config information. */
    if (type == CLUSTERMSG_TYPE_PING || type == CLUSTERMSG_TYPE_PONG ||
        type == CLUSTERMSG_TYPE_MEET)
    {
        redisLog(REDIS_DEBUG,"%s packet received: %p",
            type == CLUSTERMSG_TYPE_PING ? "ping" : "pong",
            (void*)link->node);
        if (link->node) {
            if (link->node->flags & REDIS_NODE_HANDSHAKE) {
                /* If we already have this node, try to change the
                 * IP/port of the node with the new one. */
                if (sender) {
                    redisLog(REDIS_WARNING,
                        "Handshake error: we already know node %.40s, updating the address if needed.", sender->name);
                    if (nodeUpdateAddressIfNeeded(sender,link,ntohs(hdr->port)))
                    {
                        clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                                             CLUSTER_TODO_UPDATE_STATE);
                    }
                    /* Free this node as we alrady have it. This will
                     * cause the link to be freed as well. */
                    freeClusterNode(link->node);
                    return 0;
                }

                /* First thing to do is replacing the random name with the
                 * right node name if this was an handshake stage. */
                clusterRenameNode(link->node, hdr->sender);
                redisLog(REDIS_DEBUG,"Handshake with node %.40s completed.",
                    link->node->name);
                link->node->flags &= ~REDIS_NODE_HANDSHAKE;
                link->node->flags |= flags&(REDIS_NODE_MASTER|REDIS_NODE_SLAVE);
                clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG);
            } else if (memcmp(link->node->name,hdr->sender,
                        REDIS_CLUSTER_NAMELEN) != 0)
            {
                /* If the reply has a non matching node ID we
                 * disconnect this node and set it as not having an associated
                 * address. */
                redisLog(REDIS_DEBUG,"PONG contains mismatching sender ID");
                link->node->flags |= REDIS_NODE_NOADDR;
                link->node->ip[0] = '\0';
                link->node->port = 0;
                freeClusterLink(link);
                clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG);
                /* FIXME: remove this node if we already have it.
                 *
                 * If we already have it but the IP is different, use
                 * the new one if the old node is in FAIL, PFAIL, or NOADDR
                 * status... */
                return 0;
            }
        }

        /* Update the node address if it changed. */
        if (sender && type == CLUSTERMSG_TYPE_PING &&
            !(sender->flags & REDIS_NODE_HANDSHAKE) &&
            nodeUpdateAddressIfNeeded(sender,link,ntohs(hdr->port)))
        {
            clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|CLUSTER_TODO_UPDATE_STATE);
        }

        /* Update our info about the node */
        if (link->node && type == CLUSTERMSG_TYPE_PONG) {
            link->node->pong_received = mstime();
            link->node->ping_sent = 0;

            /* The PFAIL condition can be reversed without external
             * help if it is momentary (that is, if it does not
             * turn into a FAIL state).
             *
             * The FAIL condition is also reversible under specific
             * conditions detected by clearNodeFailureIfNeeded(). */
            if (link->node->flags & REDIS_NODE_PFAIL) {
                link->node->flags &= ~REDIS_NODE_PFAIL;
                clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                                     CLUSTER_TODO_UPDATE_STATE);
            } else if (link->node->flags & REDIS_NODE_FAIL) {
                clearNodeFailureIfNeeded(link->node);
            }
        }

        /* Update master/slave state */
        if (sender) {
            if (!memcmp(hdr->slaveof,REDIS_NODE_NULL_NAME,
                sizeof(hdr->slaveof)))
            {
                /* Node is a master. */
                if (sender->flags & REDIS_NODE_SLAVE) {
                    /* Reconfigure node as master. */
                    if (sender->slaveof)
                        clusterNodeRemoveSlave(sender->slaveof,sender);
                    sender->flags &= ~REDIS_NODE_SLAVE;
                    sender->flags |= REDIS_NODE_MASTER;
                    sender->slaveof = NULL;

                    /* Update config and state. */
                    clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                                         CLUSTER_TODO_UPDATE_STATE);
                }
            } else {
                /* Node is a slave. */
                clusterNode *master = clusterLookupNode(hdr->slaveof);

                if (sender->flags & REDIS_NODE_MASTER) {
                    /* Master turned into a slave! Reconfigure the node. */
                    clusterDelNodeSlots(sender);
                    sender->flags &= ~REDIS_NODE_MASTER;
                    sender->flags |= REDIS_NODE_SLAVE;

                    /* Remove the list of slaves from the node. */
                    if (sender->numslaves) clusterNodeResetSlaves(sender);

                    /* Update config and state. */
                    clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                                         CLUSTER_TODO_UPDATE_STATE);
                }

                /* Master node changed for this slave? */
                if (sender->slaveof != master) {
                    if (sender->slaveof)
                        clusterNodeRemoveSlave(sender->slaveof,sender);
                    clusterNodeAddSlave(master,sender);
                    sender->slaveof = master;

                    /* Update config. */
                    clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG);
                }
            }
        }

        /* Update our info about served slots.
         * Note: this MUST happen after we update the master/slave state
         * so that REDIS_NODE_MASTER flag will be set. */
        if (sender && sender->flags & REDIS_NODE_MASTER) {
            int changes, j;

            changes =
                memcmp(sender->slots,hdr->myslots,sizeof(hdr->myslots)) != 0;
            if (changes) {
                clusterNode *curmaster, *newmaster = NULL;

                /* Here we set curmaster to this node or the node this node
                 * replicates to if it's a slave. In the for loop we are
                 * interested to check if slots are taken away from curmaster. */
                if (server.cluster->myself->flags & REDIS_NODE_MASTER)
                    curmaster = server.cluster->myself;
                else
                    curmaster = server.cluster->myself->slaveof;

                for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
                    if (bitmapTestBit(hdr->myslots,j)) {
                        /* We rebind the slot to the new node claiming it if:
                         * 1) The slot was unassigned.
                         * 2) The new node claims it with a greater configEpoch. */
                        if (server.cluster->slots[j] == sender) continue;
                        if (server.cluster->slots[j] == NULL ||
                            server.cluster->slots[j]->configEpoch <
                            senderConfigEpoch)
                        {
                            if (server.cluster->slots[j] == curmaster)
                                newmaster = sender;
                            clusterDelSlot(j);
                            clusterAddSlot(sender,j);
                            clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                                                 CLUSTER_TODO_UPDATE_STATE|
                                                 CLUSTER_TODO_FSYNC_CONFIG);
                        }
                    } else {
                        /* This node claims to no longer handling the slot,
                         * however we don't change our config as this is likely:
                         * 1) Rehashing in progress.
                         * 2) Failover.
                         * In both cases we'll be informed about who is serving
                         * the slot eventually. In the meantime it's up to the
                         * original owner to try to redirect our clients to the
                         * right node. */
                    }
                }

                /* If at least one slot was reassigned from a node to another node
                 * with a greater configEpoch, it is possible that:
                 * 1) We are a master is left without slots. This means that we were
                 *    failed over and we should turn into a replica of the new
                 *    master.
                 * 2) We are a slave and our master is left without slots. We need
                 *    to replicate to the new slots owner. */
                if (newmaster && curmaster->numslots == 0) {
                    redisLog(REDIS_WARNING,"Configuration change detected. Reconfiguring myself as a replica of %.40s", sender->name);
                    clusterSetMaster(sender);
                    clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                                         CLUSTER_TODO_UPDATE_STATE|
                                         CLUSTER_TODO_FSYNC_CONFIG);
                }
            }
        }

        /* Get info from the gossip section */
        clusterProcessGossipSection(hdr,link);
    } else if (type == CLUSTERMSG_TYPE_FAIL) {
        clusterNode *failing;

        if (sender) {
            failing = clusterLookupNode(hdr->data.fail.about.nodename);
            if (failing && !(failing->flags & (REDIS_NODE_FAIL|REDIS_NODE_MYSELF)))
            {
                redisLog(REDIS_NOTICE,
                    "FAIL message received from %.40s about %.40s",
                    hdr->sender, hdr->data.fail.about.nodename);
                failing->flags |= REDIS_NODE_FAIL;
                failing->fail_time = mstime();
                failing->flags &= ~REDIS_NODE_PFAIL;
                clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|CLUSTER_TODO_UPDATE_STATE);
            }
        } else {
            redisLog(REDIS_NOTICE,
                "Ignoring FAIL message from unknonw node %.40s about %.40s",
                hdr->sender, hdr->data.fail.about.nodename);
        }
    } else if (type == CLUSTERMSG_TYPE_PUBLISH) {
        robj *channel, *message;
        uint32_t channel_len, message_len;

        /* Don't bother creating useless objects if there are no
         * Pub/Sub subscribers. */
        if (dictSize(server.pubsub_channels) || listLength(server.pubsub_patterns)) {
            channel_len = ntohl(hdr->data.publish.msg.channel_len);
            message_len = ntohl(hdr->data.publish.msg.message_len);
            channel = createStringObject(
                        (char*)hdr->data.publish.msg.bulk_data,channel_len);
            message = createStringObject(
                        (char*)hdr->data.publish.msg.bulk_data+channel_len, message_len);
            pubsubPublishMessage(channel,message);
            decrRefCount(channel);
            decrRefCount(message);
        }
    } else if (type == CLUSTERMSG_TYPE_FAILOVER_AUTH_REQUEST) {
        if (!sender) return 1;  /* We don't know that node. */
        clusterSendFailoverAuthIfNeeded(sender,hdr);
    } else if (type == CLUSTERMSG_TYPE_FAILOVER_AUTH_ACK) {
        if (!sender) return 1;  /* We don't know that node. */
        /* We consider this vote only if the sender is a master serving
         * a non zero number of slots, and its currentEpoch is greater or
         * equal to epoch where this node started the election. */
        if (sender->flags & REDIS_NODE_MASTER &&
            sender->numslots > 0 &&
            senderCurrentEpoch >= server.cluster->failover_auth_epoch)
        {
            server.cluster->failover_auth_count++;
            /* Maybe we reached a quorum here, set a flag to make sure
             * we check ASAP. */
            clusterDoBeforeSleep(CLUSTER_TODO_HANDLE_FAILOVER);
        }
    } else {
        redisLog(REDIS_WARNING,"Received unknown packet type: %d", type);
    }
    return 1;
}