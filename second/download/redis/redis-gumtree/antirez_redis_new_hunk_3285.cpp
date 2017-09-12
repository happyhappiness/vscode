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
