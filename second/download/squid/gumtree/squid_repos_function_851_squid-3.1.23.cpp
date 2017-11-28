int
comm_udp_recvfrom(int fd, void *buf, size_t len, int flags, IpAddress &from)
{
    statCounter.syscalls.sock.recvfroms++;
    int x = 0;
    struct addrinfo *AI = NULL;

    debugs(5,8, "comm_udp_recvfrom: FD " << fd << " from " << from);

    assert( NULL == AI );

    from.InitAddrInfo(AI);

    x = recvfrom(fd, buf, len, flags, AI->ai_addr, &AI->ai_addrlen);

    from = *AI;

    from.FreeAddrInfo(AI);

    return x;
}