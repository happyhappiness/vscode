    }

    if (!strcasecmp(c->argv[1]->ptr,"meet") && c->argc == 4) {
        /* CLUSTER MEET <ip> <port> */
        clusterNode *n;
        struct sockaddr_storage sa;
        long port;

        /* Perform sanity checks on IP/port */
        if (inet_pton(AF_INET,c->argv[2]->ptr,
            &(((struct sockaddr_in *)&sa)->sin_addr)))
        {
            sa.ss_family = AF_INET;
        } else if (inet_pton(AF_INET6,c->argv[2]->ptr,
            &(((struct sockaddr_in6 *)&sa)->sin6_addr)))
        {
            sa.ss_family = AF_INET6;
        } else {
            addReplyError(c,"Invalid IP address in MEET");
            return;
        }
        if (getLongFromObjectOrReply(c, c->argv[3], &port, NULL) != REDIS_OK ||
                    port < 0 || port > (65535-REDIS_CLUSTER_PORT_INCR))
        {
            addReplyError(c,"Invalid TCP port specified");
            return;
        }

        /* Finally add the node to the cluster with a random name, this 
         * will get fixed in the first handshake (ping/pong). */
        n = createClusterNode(NULL,REDIS_NODE_HANDSHAKE|REDIS_NODE_MEET);

        /* Set node->ip as the normalized string representation of the node
         * IP address. */
        if (sa.ss_family == AF_INET)
            inet_ntop(AF_INET,
                (void*)&(((struct sockaddr_in *)&sa)->sin_addr),
                n->ip,REDIS_CLUSTER_IPLEN);
        else
            inet_ntop(AF_INET6,
                (void*)&(((struct sockaddr_in6 *)&sa)->sin6_addr),
                n->ip,REDIS_CLUSTER_IPLEN);
        n->port = port;
        clusterAddNode(n);
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"nodes") && c->argc == 2) {
        /* CLUSTER NODES */
        robj *o;
