void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
    uint16_t count = ntohs(hdr->count);
    clusterMsgDataGossip *g = (clusterMsgDataGossip*) hdr->data.ping.gossip;
    clusterNode *sender = link->node ? link->node : clusterLookupNode(hdr->sender);

    while(count--) {
        sds ci = sdsempty();
        uint16_t flags = ntohs(g->flags);
        clusterNode *node;

        if (flags == 0) ci = sdscat(ci,"noflags,");
        if (flags & REDIS_NODE_MYSELF) ci = sdscat(ci,"myself,");
        if (flags & REDIS_NODE_MASTER) ci = sdscat(ci,"master,");
        if (flags & REDIS_NODE_SLAVE) ci = sdscat(ci,"slave,");
        if (flags & REDIS_NODE_PFAIL) ci = sdscat(ci,"fail?,");
        if (flags & REDIS_NODE_FAIL) ci = sdscat(ci,"fail,");
        if (flags & REDIS_NODE_HANDSHAKE) ci = sdscat(ci,"handshake,");
        if (flags & REDIS_NODE_NOADDR) ci = sdscat(ci,"noaddr,");
        if (ci[sdslen(ci)-1] == ',') ci[sdslen(ci)-1] = ' ';

        redisLog(REDIS_DEBUG,"GOSSIP %.40s %s:%d %s",
            g->nodename,
            g->ip,
            ntohs(g->port),
            ci);
        sdsfree(ci);

        /* Update our state accordingly to the gossip sections */
        node = clusterLookupNode(g->nodename);
        if (node != NULL) {
            /* We already know this node. Let's start updating the last
             * time PONG figure if it is newer than our figure.
             * Note that it's not a problem if we have a PING already 
             * in progress against this node. */
            if (node->pong_received < ntohl(g->pong_received)) {
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
             * start an handshake process against this IP/PORT pairs.
             *
             * Note that we require that the sender of this gossip message
             * is a well known node in our cluster, otherwise we risk
             * joining another cluster. */
            if (sender && !(flags & REDIS_NODE_NOADDR)) {
                clusterNode *newnode;

                redisLog(REDIS_DEBUG,"Adding the new node");
                newnode = createClusterNode(NULL,REDIS_NODE_HANDSHAKE);
                memcpy(newnode->ip,g->ip,sizeof(g->ip));
                newnode->port = ntohs(g->port);
                clusterAddNode(newnode);
            }
        }

        /* Next node */
        g++;
    }
}