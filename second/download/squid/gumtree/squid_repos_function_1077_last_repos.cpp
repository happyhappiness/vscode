int
mcastSetTtl(int fd, int mcast_ttl)
{
#ifdef IP_MULTICAST_TTL
    char ttl = (char) mcast_ttl;

    if (setsockopt(fd, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, 1) < 0) {
        int xerrno = errno;
        debugs(50, DBG_IMPORTANT, "mcastSetTtl: FD " << fd << ", TTL: " << mcast_ttl << ": " << xstrerr(xerrno));
    }
#endif

    return 0;
}