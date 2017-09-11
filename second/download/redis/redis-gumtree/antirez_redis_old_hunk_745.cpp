    memcpy(node->ip,ip,sizeof(ip));
    node->port = port;
    if (node->link) freeClusterLink(node->link);
    node->flags &= ~REDIS_NODE_NOADDR;
    serverLog(LL_WARNING,"Address updated for node %.40s, now %s:%d",
        node->name, node->ip, node->port);

