    else
        ci = sdscatlen(ci," - ",3);

    /* Latency from the POV of this node, link status */
    ci = sdscatprintf(ci,"%lld %lld %llu %s",
        (long long) node->ping_sent,
        (long long) node->pong_received,
