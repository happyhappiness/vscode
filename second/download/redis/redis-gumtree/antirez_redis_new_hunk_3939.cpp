static int cliReadReply(int fd);
static void usage();

/* Connect to the client. If force is not zero the connection is performed
 * even if there is already a connected socket. */
static int cliConnect(int force) {
    char err[ANET_ERR_LEN];
    static int fd = ANET_ERR;

    if (fd == ANET_ERR || force) {
        if (force) close(fd);
        fd = anetTcpConnect(err,config.hostip,config.hostport);
        if (fd == ANET_ERR) {
            fprintf(stderr, "Could not connect to Redis at %s:%d: %s", config.hostip, config.hostport, err);
