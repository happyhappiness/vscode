 * bigger we pad our payload with newlines that are anyway ignored and truncate
 * the file afterward. */
int clusterSaveConfig(int do_fsync) {
    sds ci = clusterGenNodesDescription(REDIS_NODE_HANDSHAKE);
    size_t content_size = sdslen(ci);
    struct stat sb;
    int fd;
    
    if ((fd = open(server.cluster_configfile,O_WRONLY|O_CREAT,0644))
        == -1) goto err;
