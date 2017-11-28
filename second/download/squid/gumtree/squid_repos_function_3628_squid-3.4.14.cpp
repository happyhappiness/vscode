void
ConnStateData::stopPinnedConnectionMonitoring()
{
    if (pinning.readHandler != NULL) {
        comm_read_cancel(pinning.serverConnection->fd, pinning.readHandler);
        pinning.readHandler = NULL;
    }
}