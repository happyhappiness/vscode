 * CLUSTER command
 * -------------------------------------------------------------------------- */

void clusterCommand(redisClient *c) {
    if (server.cluster_enabled == 0) {
        addReplyError(c,"This instance has cluster support disabled");
