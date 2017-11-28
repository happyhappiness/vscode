static void
htcpSend(const char *buf, int len, Ip::Address &to)
{
    debugs(31, 3, to);
    htcpHexdump("htcpSend", buf, len);

    if (comm_udp_sendto(htcpOutgoingConn->fd, to, buf, len) < 0) {
        int xerrno = errno;
        debugs(31, 3, htcpOutgoingConn << " sendto: " << xstrerr(xerrno));
    } else
        ++statCounter.htcp.pkts_sent;
}