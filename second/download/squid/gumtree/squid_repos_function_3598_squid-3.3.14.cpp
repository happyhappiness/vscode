void
ConnStateData::startPinnedConnectionMonitoring()
{
    if (pinning.readHandler != NULL)
        return; // already monitoring

    typedef CommCbMemFunT<ConnStateData, CommIoCbParams> Dialer;
    pinning.readHandler = JobCallback(33, 3,
                                      Dialer, this, ConnStateData::clientPinnedConnectionRead);
    static char unusedBuf[8];
    comm_read(pinning.serverConnection, unusedBuf, sizeof(unusedBuf), pinning.readHandler);
}