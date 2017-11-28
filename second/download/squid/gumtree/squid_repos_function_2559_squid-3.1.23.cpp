static void
ftpSendPORT(FtpStateData * ftpState)
{
    int fd;

    IpAddress ipa;
    struct addrinfo *AI = NULL;
    unsigned char *addrptr;
    unsigned char *portptr;

    /* check the server control channel is still available */
    if (!ftpState || !ftpState->haveControlChannel("ftpSendPort"))
        return;

    if (Config.Ftp.epsv_all && ftpState->flags.epsv_all_sent) {
        debugs(9, DBG_IMPORTANT, "FTP does not allow PORT method after 'EPSV ALL' has been sent.");
        return;
    }

    debugs(9, 3, HERE);
    ftpState->flags.pasv_supported = 0;
    fd = ftpOpenListenSocket(ftpState, 0);
    ipa.InitAddrInfo(AI);

    if (getsockname(fd, AI->ai_addr, &AI->ai_addrlen)) {
        ipa.FreeAddrInfo(AI);
        debugs(9, DBG_CRITICAL, HERE << "getsockname(" << fd << ",..): " << xstrerror());

        /* XXX Need to set error message */
        ftpFail(ftpState);
        return;
    }

    if ( AI->ai_addrlen != sizeof(struct sockaddr_in) ) {
        ipa.FreeAddrInfo(AI);
        /* IPv6 CANNOT send PORT command.                           */
        /* we got here by attempting and failing an EPRT            */
        /* using the same reply code should simulate a PORT failure */
        ftpReadPORT(ftpState);
        return;
    }

    addrptr = (unsigned char *) &((struct sockaddr_in*)AI->ai_addr)->sin_addr;
    portptr = (unsigned char *) &((struct sockaddr_in*)AI->ai_addr)->sin_port;
    snprintf(cbuf, 1024, "PORT %d,%d,%d,%d,%d,%d\r\n",
             addrptr[0], addrptr[1], addrptr[2], addrptr[3],
             portptr[0], portptr[1]);
    ftpState->writeCommand(cbuf);
    ftpState->state = SENT_PORT;

    ipa.FreeAddrInfo(AI);
}