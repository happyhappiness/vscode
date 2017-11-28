int
comm_udp_sendto(int fd,
                const Ip::Address &to_addr,
                const void *buf,
                int len)
{
    PROF_start(comm_udp_sendto);
    ++ statCounter.syscalls.sock.sendtos;

    debugs(50, 3, "comm_udp_sendto: Attempt to send UDP packet to " << to_addr <<
           " using FD " << fd << " using Port " << comm_local_port(fd) );

    struct addrinfo *AI = NULL;
    to_addr.getAddrInfo(AI, fd_table[fd].sock_family);
    int x = sendto(fd, buf, len, 0, AI->ai_addr, AI->ai_addrlen);
    Ip::Address::FreeAddr(AI);

    PROF_stop(comm_udp_sendto);

    if (x >= 0)
        return x;

#if _SQUID_LINUX_

    if (ECONNREFUSED != errno)
#endif

        debugs(50, DBG_IMPORTANT, "comm_udp_sendto: FD " << fd << ", (family=" << fd_table[fd].sock_family << ") " << to_addr << ": " << xstrerror());

    return Comm::COMM_ERROR;
}