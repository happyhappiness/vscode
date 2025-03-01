int
IcmpSquid::Open(void)
{
#if USE_ICMP
    const char *args[2];
    int rfd;
    int wfd;
    Ip::Address localhost;

    /* User configured disabled. */
    if (!IcmpCfg.enable) {
        Close();
        return -1;
    }

    args[0] = "(pinger)";
    args[1] = NULL;
    localhost.setLocalhost();

    /*
     * Do NOT use IPC_DGRAM (=IPC_UNIX_DGRAM) here because you can't
     * send() more than 4096 bytes on a socketpair() socket (at
     * least on FreeBSD).
     */
    pid = ipcCreate(IPC_UDP_SOCKET,
                    IcmpCfg.program.c_str(),
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

    Comm::SetSelect(icmp_sock, COMM_SELECT_READ, icmpSquidRecv, NULL, 0);

    commUnsetFdTimeout(icmp_sock);

    debugs(37, DBG_IMPORTANT, HERE << "Pinger socket opened on FD " << icmp_sock);

    /* Tests the pinger immediately using localhost */
    if (Ip::EnableIpv6)
        SendEcho(localhost, S_ICMP_ECHO, "ip6-localhost");
    if (localhost.setIPv4())
        SendEcho(localhost, S_ICMP_ECHO, "localhost");

#if _SQUID_WINDOWS_

    debugs(37, 4, HERE << "Pinger handle: 0x" << std::hex << hIpc << std::dec << ", PID: " << pid);

#endif /* _SQUID_WINDOWS_ */
    return icmp_sock;
#else /* USE_ICMP */
    return -1;
#endif /* USE_ICMP */
}