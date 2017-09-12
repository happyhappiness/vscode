char *sentinelVoteLeader(sentinelRedisInstance *master, uint64_t req_epoch, char *req_runid, uint64_t *leader_epoch) {
    sentinelRedisInstance *si = sentinelGetSentinelByRunid(master,req_runid);

    if (req_epoch > sentinel.current_epoch)
        sentinel.current_epoch = req_epoch;

    if (si && master->leader_epoch < req_epoch &&
              sentinel.current_epoch <= req_epoch)
    {
        sdsfree(master->leader);
        master->leader = sdsnew(req_runid);
        master->leader_epoch = sentinel.current_epoch;
    }

    *leader_epoch = master->leader_epoch;
    return master->leader;
}