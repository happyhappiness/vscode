/* Generate a csv-alike representation of the specified cluster node.
 * See clusterGenNodesDescription() top comment for more information.
 *
 * The function appends the node representation to the SDS string 'ci' and
 * returns it (that may point to a different string as usually with the
 * SDS-style API). */
sds clusterGenNodeDescription(sds ci, clusterNode *node) {
    int j, start;

    /* Node coordinates */
    ci = sdscatlen(ci,node->name,40);
    ci = sdscatfmt(ci," %s:%i ",node->ip,node->port);

    /* Flags */
    ci = representRedisNodeFlags(ci, node->flags);

    /* Slave of... or just "-" */
    if (node->slaveof) {
        ci = sdscatlen(ci," ",1);
        ci = sdscatlen(ci,node->slaveof->name,40);
        ci = sdscatlen(ci," ",1);
    } else {
        ci = sdscatlen(ci," - ",3);
    }

    /* Latency from the POV of this node, link status */
    ci = sdscatfmt(ci,"%I %I %U %s",
        (long long) node->ping_sent,
        (long long) node->pong_received,
        (unsigned long long) node->configEpoch,
