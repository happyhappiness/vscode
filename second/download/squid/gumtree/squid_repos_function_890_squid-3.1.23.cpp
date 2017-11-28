int
comm_udp_sendto(int fd,
                const IpAddress &to_addr,
                const void *buf,
                int len)
{
    int x = 0;
    struct addrinfo *AI = NULL;

    PROF_start(comm_udp_sendto);
    statCounter.syscalls.sock.sendtos++;

    debugs(50, 3, "comm_udp_sendto: Attempt to send UDP packet to " << to_addr <<
           " using FD " << fd << " using Port " << comm_local_port(fd) );

    /* BUG: something in the above macro appears to occasionally be setting AI to garbage. */
    /* AYJ: 2007-08-27 : or was it because I wasn't then setting 'fd_table[fd].sock_family' to fill properly. */
    assert( NULL == AI );

    to_addr.GetAddrInfo(AI, fd_table[fd].sock_family);

    x = sendto(fd, buf, len, 0, AI->ai_addr, AI->ai_addrlen);

    to_addr.FreeAddrInfo(AI);

    PROF_stop(comm_udp_sendto);

    if (x >= 0)
        return x;

#ifdef _SQUID_LINUX_

    if (ECONNREFUSED != errno)
#endif

        debugs(50, 1, "comm_udp_sendto: FD " << fd << ", (family=" << fd_table[fd].sock_family << ") " << to_addr << ": " << xstrerror());

    return COMM_ERROR;
}