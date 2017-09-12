static int cliReadReply(int fd);
static void usage();

/* Connect to the client. If force is not zero the connection is performed
 * even if there is already a connected socket. */
static int cliConnect(int force) {
