int
comm_set_tos(int fd, int tos)
{
#ifdef IP_TOS
    int x = setsockopt(fd, IPPROTO_IP, IP_TOS, (char *) &tos, sizeof(int));
    if (x < 0)
        debugs(50, 1, "comm_set_tos: setsockopt(IP_TOS) on FD " << fd << ": " << xstrerror());
    return x;
#else
    debugs(50, 0, "WARNING: setsockopt(IP_TOS) not supported on this platform");
    return -1;
#endif
}