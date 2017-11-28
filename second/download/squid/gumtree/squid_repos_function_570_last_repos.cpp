void
comm_set_v6only(int fd, int tos)
{
#ifdef IPV6_V6ONLY
    if (setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, (char *) &tos, sizeof(int)) < 0) {
        int xerrno = errno;
        debugs(50, DBG_IMPORTANT, MYNAME << "setsockopt(IPV6_V6ONLY) " << (tos?"ON":"OFF") << " for FD " << fd << ": " << xstrerr(xerrno));
    }
#else
    debugs(50, DBG_CRITICAL, MYNAME << "WARNING: setsockopt(IPV6_V6ONLY) not supported on this platform");
#endif /* sockopt */
}