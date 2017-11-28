static int
fdIsUdpListen(int fd)
{
    if (icpIncomingConn != NULL && icpIncomingConn->fd == fd)
        return 1;

    if (icpOutgoingConn != NULL && icpOutgoingConn->fd == fd)
        return 1;

    return 0;
}