    if (server.cluster->myself->numslots == 0) return;

    /* Request epoch must be >= our currentEpoch. */
    if (requestCurrentEpoch < server.cluster->currentEpoch) return;

    /* I already voted for this epoch? Return ASAP. */
    if (server.cluster->last_vote_epoch == server.cluster->currentEpoch) return;

    /* Node must be a slave and its master down. */
    if (!(node->flags & REDIS_NODE_SLAVE) ||
        master == NULL ||
        !(master->flags & REDIS_NODE_FAIL)) return;

    /* We did not voted for a slave about this master for two
     * times the node timeout. This is not strictly needed for correctness
     * of the algorithm but makes the base case more linear. */
    if (mstime() - node->slaveof->voted_time < server.cluster_node_timeout * 2)
        return;

    /* The slave requesting the vote must have a configEpoch for the claimed
     * slots that is >= the one of the masters currently serving the same
