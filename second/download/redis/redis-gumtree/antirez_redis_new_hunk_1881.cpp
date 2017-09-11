
    /* Slave of... or just "-" */
    if (node->slaveof)
        ci = sdscatprintf(ci," %.40s ",node->slaveof->name);
    else
        ci = sdscatlen(ci," - ",3);

    /* Latency from the POV of this node, link status */
    ci = sdscatprintf(ci,"%lld %lld %llu %s",
