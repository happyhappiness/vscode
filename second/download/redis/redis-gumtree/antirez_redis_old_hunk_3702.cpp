    char *hostsocket;
    long repeat;
    int dbnum;
    int argn_from_stdin;
    int interactive;
    int shutdown;
    int monitor_mode;
    int pubsub_mode;
    int raw_output;
    char *auth;
    char *historyfile;
} config;

static int cliReadReply(int fd);
static void usage();

static int cliConnect(void) {
    char err[ANET_ERR_LEN];
    static int fd = ANET_ERR;

    if (fd == ANET_ERR) {
        if (config.hostsocket == NULL) {
            fd = anetTcpConnect(err,config.hostip,config.hostport);
        } else {
            fd = anetUnixConnect(err,config.hostsocket);
            if (fd == ANET_ERR) {
                fprintf(stderr, "Could not connect to Redis at %s: %s", config.hostsocket, err);
                return -1;
            }
        }
        if (fd == ANET_ERR) {
            fprintf(stderr,"Could not connect to Redis at ");
