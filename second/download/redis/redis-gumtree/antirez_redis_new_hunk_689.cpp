 * handshake in order to reactivate the cached master.
 */
void replicationCacheMaster(client *c) {
    serverAssert(server.master != NULL && server.cached_master == NULL);
    serverLog(LL_NOTICE,"Caching the disconnected master state.");

    /* Unlink the client from the server structures. */
    unlinkClient(c);

    /* Save the master. Server.master will be set to null later by
     * replicationHandleMasterDisconnection(). */
    server.cached_master = server.master;

    /* Invalidate the Peer ID cache. */
    if (c->peerid) {
        sdsfree(c->peerid);
