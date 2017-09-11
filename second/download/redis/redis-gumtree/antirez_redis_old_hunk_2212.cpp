        /* If we reached this point we found a slot that in our current slots
         * is served by a master with a greater configEpoch than the one claimed
         * by the slave requesting our vote. Refuse to vote for this slave. */
        return;
    }

    /* We can vote for this slave. */
    clusterSendFailoverAuth(node);
    server.cluster->last_vote_epoch = server.cluster->currentEpoch;
    node->slaveof->voted_time = mstime();
