     * it is safe to call during packet processing. */
    if (link == node->link) return 0;

    nodeIp2String(ip,link,hdr->myip);
    if (node->port == port && node->cport == cport &&
        strcmp(ip,node->ip) == 0) return 0;

    /* IP / port is different, update it. */
    memcpy(node->ip,ip,sizeof(ip));
    node->port = port;
    node->cport = cport;
    if (node->link) freeClusterLink(node->link);
    node->flags &= ~CLUSTER_NODE_NOADDR;
    serverLog(LL_WARNING,"Address updated for node %.40s, now %s:%d",
