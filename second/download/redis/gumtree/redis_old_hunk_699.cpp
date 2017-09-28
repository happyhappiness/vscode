 * The function returns the string representation as an SDS string. */
sds clusterGenNodeDescription(clusterNode *node) {
    int j, start;
    sds ci;

    /* Node coordinates */
    ci = sdscatprintf(sdsempty(),"%.40s %s:%d ",
        node->name,
        node->ip,
        node->port);

    /* Flags */
    ci = representClusterNodeFlags(ci, node->flags);

    /* Slave of... or just "-" */
    if (node->slaveof)
