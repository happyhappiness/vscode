 *    sending it to the slave.
 * 3) Update the count of good slaves. */
void putSlaveOnline(client *slave) {
    slave->replstate = SLAVE_STATE_ONLINE;
    slave->repl_put_online_on_ack = 0;
    slave->repl_ack_time = server.unixtime; /* Prevent false timeout. */
    if (aeCreateFileEvent(server.el, slave->fd, AE_WRITABLE,
        sendReplyToClient, slave) == AE_ERR) {
        serverLog(LL_WARNING,"Unable to register writable event for slave bulk transfer: %s", strerror(errno));
        freeClient(slave);
        return;
    }
    refreshGoodSlavesCount();
    serverLog(LL_NOTICE,"Synchronization with slave %s succeeded",
        replicationGetSlaveName(slave));
}

void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
    client *slave = privdata;
    UNUSED(el);
    UNUSED(mask);
    char buf[PROTO_IOBUF_LEN];
    ssize_t nwritten, buflen;

    /* Before sending the RDB file, we send the preamble as configured by the
