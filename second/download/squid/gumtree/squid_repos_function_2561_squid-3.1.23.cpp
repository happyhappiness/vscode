static void
ftpSendEPRT(FtpStateData * ftpState)
{
    if (Config.Ftp.epsv_all && ftpState->flags.epsv_all_sent) {
        debugs(9, DBG_IMPORTANT, "FTP does not allow EPRT method after 'EPSV ALL' has been sent.");
        return;
    }

    if (!Config.Ftp.eprt) {
        /* Disabled. Switch immediately to attempting old PORT command. */
        debugs(9, 3, "EPRT disabled by local administrator");
        ftpSendPORT(ftpState);
        return;
    }

    int fd;
    IpAddress addr;
    struct addrinfo *AI = NULL;
    char buf[MAX_IPSTRLEN];

    debugs(9, 3, HERE);
    ftpState->flags.pasv_supported = 0;
    fd = ftpOpenListenSocket(ftpState, 0);

    addr.InitAddrInfo(AI);

    if (getsockname(fd, AI->ai_addr, &AI->ai_addrlen)) {
        addr.FreeAddrInfo(AI);
        debugs(9, DBG_CRITICAL, HERE << "getsockname(" << fd << ",..): " << xstrerror());

        /* XXX Need to set error message */
        ftpFail(ftpState);
        return;
    }

    addr = *AI;

    /* RFC 2428 defines EPRT as IPv6 equivalent to IPv4 PORT command. */
    /* Which can be used by EITHER protocol. */
    snprintf(cbuf, 1024, "EPRT |%d|%s|%d|\r\n",
             ( addr.IsIPv6() ? 2 : 1 ),
             addr.NtoA(buf,MAX_IPSTRLEN),
             addr.GetPort() );

    ftpState->writeCommand(cbuf);
    ftpState->state = SENT_EPRT;

    addr.FreeAddrInfo(AI);
}