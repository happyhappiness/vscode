    char *hostsocket;
    long repeat;
    int dbnum;
    int interactive;
    int shutdown;
    int monitor_mode;
    int pubsub_mode;
    int raw_output; /* output mode per command */
    int tty; /* flag for default output format */
    int stdinarg; /* get last arg from stdin. (-x option) */
    char mb_sep;
    char *auth;
    char *historyfile;
} config;

static int cliReadReply(int fd);
static void usage();

/* Connect to the client. If force is not zero the connection is performed
 * even if there is already a connected socket. */
static int cliConnect(int force) {
    char err[ANET_ERR_LEN];
    static int fd = ANET_ERR;

    if (fd == ANET_ERR || force) {
        if (force) close(fd);
        if (config.hostsocket == NULL) {
            fd = anetTcpConnect(err,config.hostip,config.hostport);
        } else {
            fd = anetUnixConnect(err,config.hostsocket);
        }
        if (fd == ANET_ERR) {
            fprintf(stderr,"Could not connect to Redis at ");
