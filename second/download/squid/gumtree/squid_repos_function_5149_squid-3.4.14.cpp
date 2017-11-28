void
Comm::ConnOpener::connected()
{
    Must(temporaryFd_ >= 0);
    keepFd();

    /*
     * stats.conn_open is used to account for the number of
     * connections that we have open to the CachePeer, so we can limit
     * based on the max-conn option.  We need to increment here,
     * even if the connection may fail.
     */
    if (CachePeer *peer=(conn_->getPeer()))
        ++peer->stats.conn_open;

    lookupLocalAddress();

    /* TODO: remove these fd_table accesses. But old code still depends on fd_table flags to
     *       indicate the state of a raw fd object being passed around.
     *       Also, legacy code still depends on comm_local_port() with no access to Comm::Connection
     *       when those are done comm_local_port can become one of our member functions to do the below.
     */
    Must(fd_table[conn_->fd].flags.open);
    fd_table[conn_->fd].local_addr = conn_->local;

    sendAnswer(COMM_OK, 0, "Comm::ConnOpener::connected");
}