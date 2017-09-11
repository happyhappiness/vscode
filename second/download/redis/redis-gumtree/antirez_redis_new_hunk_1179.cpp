
/* Helper function. Trims query buffer to make the function that processes
 * multi bulk requests idempotent. */
static void setProtocolError(client *c, int pos) {
    if (server.verbosity <= REDIS_VERBOSE) {
        sds client = catClientInfoString(sdsempty(),c);
        serverLog(REDIS_VERBOSE,
