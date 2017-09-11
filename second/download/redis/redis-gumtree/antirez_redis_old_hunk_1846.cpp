        node->port);

    /* Flags */
    if (node->flags == 0) ci = sdscat(ci,"noflags,");
    if (node->flags & REDIS_NODE_MYSELF) ci = sdscat(ci,"myself,");
    if (node->flags & REDIS_NODE_MASTER) ci = sdscat(ci,"master,");
    if (node->flags & REDIS_NODE_SLAVE) ci = sdscat(ci,"slave,");
    if (node->flags & REDIS_NODE_PFAIL) ci = sdscat(ci,"fail?,");
    if (node->flags & REDIS_NODE_FAIL) ci = sdscat(ci,"fail,");
    if (node->flags & REDIS_NODE_HANDSHAKE) ci =sdscat(ci,"handshake,");
    if (node->flags & REDIS_NODE_NOADDR) ci = sdscat(ci,"noaddr,");
    if (ci[sdslen(ci)-1] == ',') ci[sdslen(ci)-1] = ' ';

    /* Slave of... or just "-" */
    if (node->slaveof)
        ci = sdscatprintf(ci,"%.40s ",node->slaveof->name);
    else
        ci = sdscatprintf(ci,"- ");

    /* Latency from the POV of this node, link status */
    ci = sdscatprintf(ci,"%lld %lld %llu %s",
