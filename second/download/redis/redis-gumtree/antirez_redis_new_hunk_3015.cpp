    return;
}

/* The ASKING command is required after a -ASK redirection.
 * The client should issue ASKING before to actualy send the command to
 * the target instance. See the Redis Cluster specification for more
 * information. */
void askingCommand(redisClient *c) {
    if (server.cluster_enabled == 0) {
        addReplyError(c,"This instance has cluster support disabled");
        return;
    }
    c->flags |= REDIS_ASKING;
    addReply(c,shared.ok);
}

/* -----------------------------------------------------------------------------
 * Cluster functions related to serving / redirecting clients
 * -------------------------------------------------------------------------- */
