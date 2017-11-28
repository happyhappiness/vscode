int
IcmpSquid::Open(void)
{
#if USE_ICMP
    const char *args[2];
    int rfd;
    int wfd;
    IpAddress localhost;

    /* User configured disabled. */
    if (!Config.pinger.enable) {
        Close();
        return -1;
    }

    args[0] = "(pinger)";
    args[1] = NULL;
    localhost.SetLocalhost();

    /*
     * Do NOT use IPC_DGRAM (=IPC_UNIX_DGRAM) here because you can't
     * send() more than 4096 bytes on a socketpair() socket (at
     * least on FreeBSD).
     */
    pid = ipcCreate(IPC_UDP_SOCKET,
                    Config.pinger.program,
                    args,
                    "Pinger Socket",
                    localhost,
                    &rfd,
                    &wfd,
                    &hIpc);

    if (pid < 0)
        return -1;

    assert(rfd == wfd);

    icmp_sock = rfd;

    fd_note(icmp_sock, "pinger");

    commSetSelect(icmp_sock, COMM_SELECT_READ, icmpSquidRecv, NULL, 0);

    commSetTimeout(icmp_sock, -1, NULL, NULL);

    debugs(37, 1, HERE << "Pinger socket opened on FD " << icmp_sock);

    /* Tests the pinger immediately using localhost */
    if (Ip::EnableIpv6)
        SendEcho(localhost, S_ICMP_ECHO, "ip6-localhost");
    if (localhost.SetIPv4())
        SendEcho(localhost, S_ICMP_ECHO, "localhost");

#ifdef _SQUID_MSWIN_

    debugs(37, 4, HERE << "Pinger handle: 0x" << std::hex << hIpc << std::dec << ", PID: " << pid);

#endif /* _SQUID_MSWIN_ */
    return icmp_sock;
#else /* USE_ICMP */
    return -1;
#endif /* USE_ICMP */
}