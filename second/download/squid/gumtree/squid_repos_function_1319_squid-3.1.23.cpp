int
mcastSetTtl(int fd, int mcast_ttl)
{
#ifdef IP_MULTICAST_TTL
    char ttl = (char) mcast_ttl;

    if (setsockopt(fd, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, 1) < 0)
        debugs(50, 1, "comm_set_mcast_ttl: FD " << fd << ", TTL: " << mcast_ttl << ": " << xstrerror());

#endif

    return 0;
}