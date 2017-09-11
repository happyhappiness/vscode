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
                failing->fail_time = time(NULL);
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
