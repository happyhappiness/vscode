
    /* Log link disconnection with slave */
    if ((c->flags & REDIS_SLAVE) && !(c->flags & REDIS_MONITOR)) {
        serverLog(REDIS_WARNING,"Connection with slave %s lost.",
            replicationGetSlaveName(c));
    }

