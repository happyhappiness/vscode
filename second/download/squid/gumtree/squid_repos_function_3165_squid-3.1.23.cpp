static int
fdIsIcp(int fd)
{
    if (fd == theInIcpConnection)
        return 1;

    if (fd == theOutIcpConnection)
        return 1;

    return 0;
}