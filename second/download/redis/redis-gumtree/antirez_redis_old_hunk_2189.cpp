    if (server.cluster->myself->numslots == 0) return;

    /* Request epoch must be >= our currentEpoch. */
    if (requestCurrentEpoch < server.cluster->currentEpoch) {
        printf("REFUSED BECAUSE OF EPOCH\n");
        return;
    }

    /* I already voted for this epoch? Return ASAP. */
    if (server.cluster->last_vote_epoch == server.cluster->currentEpoch) {
        printf("REFUSED BECAUSE ALREADY VOTED FOR EPOCH\n");
        return;
    }

    /* Node must be a slave and its master down. */
    if (!(node->flags & REDIS_NODE_SLAVE) ||
        master == NULL ||
        !(master->flags & REDIS_NODE_FAIL))
    {
        printf("REFUSED BECAUSE NOT A SLAVE OR MASTER NOT FAIL.\n");
        return;
    }

    /* We did not voted for a slave about this master for two
     * times the node timeout. This is not strictly needed for correctness
     * of the algorithm but makes the base case more linear. */
    if (mstime() - node->slaveof->voted_time < server.cluster_node_timeout * 2)
    {
        printf("REFUSED BECAUSE ALREADY VOTED WITHIN NODE_TIMEOUT*2.\n");
        return;
    }

    /* The slave requesting the vote must have a configEpoch for the claimed
     * slots that is >= the one of the masters currently serving the same
