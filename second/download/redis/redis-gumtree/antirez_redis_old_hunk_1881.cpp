
    /* Slave of... or just "-" */
    if (node->slaveof)
        ci = sdscatprintf(ci,"%.40s ",node->slaveof->name);
    else
        ci = sdscatprintf(ci,"- ");

    /* Latency from the POV of this node, link status */
    ci = sdscatprintf(ci,"%lld %lld %llu %s",
