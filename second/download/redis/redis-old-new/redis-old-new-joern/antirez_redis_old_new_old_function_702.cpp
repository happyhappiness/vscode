void clusterUpdateState(void) {
    int j, new_state;
    int reachable_masters = 0;
    static mstime_t among_minority_time;
    static mstime_t first_call_time = 0;

    server.cluster->todo_before_sleep &= ~CLUSTER_TODO_UPDATE_STATE;

    /* If this is a master node, wait some time before turning the state
     * into OK, since it is not a good idea to rejoin the cluster as a writable
     * master, after a reboot, without giving the cluster a chance to
     * reconfigure this node. Note that the delay is calculated starting from
     * the first call to this function and not since the server start, in order
     * to don't count the DB loading time. */
    if (first_call_time == 0) first_call_time = mstime();
    if (nodeIsMaster(myself) &&
        server.cluster->state == REDIS_CLUSTER_FAIL &&
        mstime() - first_call_time < REDIS_CLUSTER_WRITABLE_DELAY) return;

    /* Start assuming the state is OK. We'll turn it into FAIL if there
     * are the right conditions. */
    new_state = REDIS_CLUSTER_OK;

    /* Check if all the slots are covered. */
    if (server.cluster_require_full_coverage) {
        for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
            if (server.cluster->slots[j] == NULL ||
                server.cluster->slots[j]->flags & (REDIS_NODE_FAIL))
            {
                new_state = REDIS_CLUSTER_FAIL;
                break;
            }
        }
    }

    /* Compute the cluster size, that is the number of master nodes
     * serving at least a single slot.
     *
     * At the same time count the number of reachable masters having
     * at least one slot. */
    {
        dictIterator *di;
        dictEntry *de;

        server.cluster->size = 0;
        di = dictGetSafeIterator(server.cluster->nodes);
        while((de = dictNext(di)) != NULL) {
            clusterNode *node = dictGetVal(de);

            if (nodeIsMaster(node) && node->numslots) {
                server.cluster->size++;
                if ((node->flags & (REDIS_NODE_FAIL|REDIS_NODE_PFAIL)) == 0)
                    reachable_masters++;
            }
        }
        dictReleaseIterator(di);
    }

    /* If we are in a minority partition, change the cluster state
     * to FAIL. */
    {
        int needed_quorum = (server.cluster->size / 2) + 1;

        if (reachable_masters < needed_quorum) {
            new_state = REDIS_CLUSTER_FAIL;
            among_minority_time = mstime();
        }
    }

    /* Log a state change */
    if (new_state != server.cluster->state) {
        mstime_t rejoin_delay = server.cluster_node_timeout;

        /* If the instance is a master and was partitioned away with the
         * minority, don't let it accept queries for some time after the
         * partition heals, to make sure there is enough time to receive
         * a configuration update. */
        if (rejoin_delay > REDIS_CLUSTER_MAX_REJOIN_DELAY)
            rejoin_delay = REDIS_CLUSTER_MAX_REJOIN_DELAY;
        if (rejoin_delay < REDIS_CLUSTER_MIN_REJOIN_DELAY)
            rejoin_delay = REDIS_CLUSTER_MIN_REJOIN_DELAY;

        if (new_state == REDIS_CLUSTER_OK &&
            nodeIsMaster(myself) &&
            mstime() - among_minority_time < rejoin_delay)
        {
            return;
        }

        /* Change the state and log the event. */
        serverLog(LL_WARNING,"Cluster state changed: %s",
            new_state == REDIS_CLUSTER_OK ? "ok" : "fail");
        server.cluster->state = new_state;
    }
}