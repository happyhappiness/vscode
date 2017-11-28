static void
htcpSend(const char *buf, int len, Ip::Address &to)
{
    debugs(31, 3, HERE << to);
    htcpHexdump("htcpSend", buf, len);

    if (comm_udp_sendto(htcpOutgoingConn->fd, to, buf, len) < 0)
        debugs(31, 3, HERE << htcpOutgoingConn << " sendto: " << xstrerror());
    else
        ++statCounter.htcp.pkts_sent;
}