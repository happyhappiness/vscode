void
comm_set_v6only(int fd, int tos)
{
#ifdef IPV6_V6ONLY
    if (setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, (char *) &tos, sizeof(int)) < 0) {
        debugs(50, 1, "comm_open: setsockopt(IPV6_V6ONLY) " << (tos?"ON":"OFF") << " for FD " << fd << ": " << xstrerror());
    }
#else
    debugs(50, 0, "WARNING: comm_open: setsockopt(IPV6_V6ONLY) not supported on this platform");
#endif /* sockopt */
}