 * If a vote is not available returns NULL, otherwise return the Sentinel
 * runid and populate the leader_epoch with the epoch of the last vote. */
char *sentinelVoteLeader(sentinelRedisInstance *master, uint64_t req_epoch, char *req_runid, uint64_t *leader_epoch) {
    if (req_epoch > sentinel.current_epoch)
        sentinel.current_epoch = req_epoch;

    if (master->leader_epoch < req_epoch && sentinel.current_epoch <= req_epoch) {
        sdsfree(master->leader);
        master->leader = sdsnew(req_runid);
        master->leader_epoch = sentinel.current_epoch;
        printf("Selected leader %s for epoch %llu\n", master->leader,
            (unsigned long long) master->leader_epoch);
    }

    *leader_epoch = master->leader_epoch;
