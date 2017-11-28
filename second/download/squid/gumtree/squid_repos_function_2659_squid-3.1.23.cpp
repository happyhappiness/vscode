static void

htcpSend(const char *buf, int len, IpAddress &to)
{
    int x;

    debugs(31, 3, "htcpSend: " << to );
    htcpHexdump("htcpSend", buf, len);

    x = comm_udp_sendto(htcpOutSocket,
                        to,
                        buf,
                        len);

    if (x < 0)
        debugs(31, 3, "htcpSend: FD " << htcpOutSocket << " sendto: " << xstrerror());
    else
        statCounter.htcp.pkts_sent++;
}