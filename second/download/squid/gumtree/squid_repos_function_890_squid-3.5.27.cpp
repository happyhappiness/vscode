int
comm_udp_recv(int fd, void *buf, size_t len, int flags)
{
    Ip::Address nul;
    return comm_udp_recvfrom(fd, buf, len, flags, nul);
}