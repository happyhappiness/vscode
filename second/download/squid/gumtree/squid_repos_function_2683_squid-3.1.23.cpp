static void
htcpRecv(int fd, void *data)
{
    static char buf[8192];
    int len;
    static IpAddress from;

    /* Receive up to 8191 bytes, leaving room for a null */

    len = comm_udp_recvfrom(fd, buf, sizeof(buf) - 1, 0, from);

    debugs(31, 3, "htcpRecv: FD " << fd << ", " << len << " bytes from " << from );

    if (len)
        statCounter.htcp.pkts_recv++;

    htcpHandleMsg(buf, len, from);

    commSetSelect(fd, COMM_SELECT_READ, htcpRecv, NULL, 0);
}