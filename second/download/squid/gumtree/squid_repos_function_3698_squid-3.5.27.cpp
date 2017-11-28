void
ConnStateData::stopPinnedConnectionMonitoring()
{
    if (pinning.readHandler != NULL) {
        Comm::ReadCancel(pinning.serverConnection->fd, pinning.readHandler);
        pinning.readHandler = NULL;
    }
}