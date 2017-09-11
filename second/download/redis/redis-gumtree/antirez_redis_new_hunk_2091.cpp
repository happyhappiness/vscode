 * bigger we pad our payload with newlines that are anyway ignored and truncate
 * the file afterward. */
int clusterSaveConfig(int do_fsync) {
    sds ci;
    size_t content_size;
    struct stat sb;
    int fd;

    /* Get the nodes description and concatenate our "vars" directive to
     * save currentEpoch and last_vote_epoch. */
    ci = clusterGenNodesDescription(REDIS_NODE_HANDSHAKE);
    ci = sdscatprintf(ci,"vars currentEpoch %llu last_vote_epoch %llu\n",
        (unsigned long long) server.cluster->currentEpoch,
        (unsigned long long) server.cluster->last_vote_epoch);
    content_size = sdslen(ci);
    
    if ((fd = open(server.cluster_configfile,O_WRONLY|O_CREAT,0644))
        == -1) goto err;
