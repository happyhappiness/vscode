int
comm_udp_recvfrom(int fd, void *buf, size_t len, int flags, Ip::Address &from)
{
    ++ statCounter.syscalls.sock.recvfroms;
    debugs(5,8, "comm_udp_recvfrom: FD " << fd << " from " << from);
    struct addrinfo *AI = NULL;
    Ip::Address::InitAddr(AI);
    int x = recvfrom(fd, buf, len, flags, AI->ai_addr, &AI->ai_addrlen);
    from = *AI;
    Ip::Address::FreeAddr(AI);
    return x;
}