            changes =
                memcmp(sender->slots,hdr->myslots,sizeof(hdr->myslots)) != 0;
            if (changes) {
                for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
                    if (bitmapTestBit(hdr->myslots,j)) {
                        /* If this slot was not served, or served by a node
                         * in FAIL state, update the table with the new node
                         * claiming to serve the slot. */
                        if (server.cluster->slots[j] == sender) continue;
                        if (server.cluster->slots[j] == NULL ||
                            server.cluster->slots[j]->flags & REDIS_NODE_FAIL)
                        {
                            clusterDelSlot(j);
                            clusterAddSlot(sender,j);
                            update_state = update_config = 1;
                        }
                    } else {
                        /* This node claims to no longer handling the slot,
                         * however we don't change our config as this is likely
                         * happening because a resharding is in progress, and
                         * it already knows where to redirect clients. */
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
        if (failing && !(failing->flags & (REDIS_NODE_FAIL|REDIS_NODE_MYSELF)))
        {
            redisLog(REDIS_NOTICE,
                "FAIL message received from %.40s about %.40s",
                hdr->sender, hdr->data.fail.about.nodename);
            failing->flags |= REDIS_NODE_FAIL;
            failing->fail_time = time(NULL);
            failing->flags &= ~REDIS_NODE_PFAIL;
            clusterUpdateState();
            clusterSaveConfigOrDie();
        }
    } else if (type == CLUSTERMSG_TYPE_PUBLISH) {
        robj *channel, *message;
        uint32_t channel_len, message_len;

        /* Don't bother creating useless objects if there are no Pub/Sub subscribers. */
        if (dictSize(server.pubsub_channels) || listLength(server.pubsub_patterns)) {
            channel_len = ntohl(hdr->data.publish.msg.channel_len);
            message_len = ntohl(hdr->data.publish.msg.message_len);
