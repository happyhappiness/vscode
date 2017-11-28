void
FwdState::syncWithServerConn(const char *host)
{
    if (Ip::Qos::TheConfig.isAclTosActive())
        Ip::Qos::setSockTos(serverConn, GetTosToServer(request));

#if SO_MARK
    if (Ip::Qos::TheConfig.isAclNfmarkActive())
        Ip::Qos::setSockNfmark(serverConn, GetNfmarkToServer(request));
#endif

    syncHierNote(serverConn, host);
}