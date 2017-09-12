void putSlaveOnline(redisClient *slave) {
    slave->replstate = REDIS_REPL_ONLINE;
    slave->repl_ack_time = server.unixtime;
    if (aeCreateFileEvent(server.el, slave->fd, AE_WRITABLE,
        sendReplyToClient, slave) == AE_ERR) {
        redisLog(REDIS_WARNING,"Unable to register writable event for slave bulk transfer: %s", strerror(errno));
        freeClient(slave);
        return;
    }
    refreshGoodSlavesCount();
}