static int
fdIsUdpListener(int fd)
{
    if (icpIncomingConn != NULL && fd == icpIncomingConn->fd)
        return 1;

    if (icpOutgoingConn != NULL && fd == icpOutgoingConn->fd)
        return 1;

    return 0;
}