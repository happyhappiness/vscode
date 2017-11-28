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

    debugs(9, 3, HERE);
    ftpState->flags.pasv_supported = 0;

    ftpOpenListenSocket(ftpState, 0);
    debugs(9, 3, "Listening for FTP data connection with FD " << ftpState->data.conn);
    if (!Comm::IsConnOpen(ftpState->data.conn)) {
        /* XXX Need to set error message */
        ftpFail(ftpState);
        return;
    }

    char buf[MAX_IPSTRLEN];

    /* RFC 2428 defines EPRT as IPv6 equivalent to IPv4 PORT command. */
    /* Which can be used by EITHER protocol. */
    snprintf(cbuf, CTRL_BUFLEN, "EPRT |%d|%s|%d|\r\n",
             ( ftpState->data.listenConn->local.isIPv6() ? 2 : 1 ),
             ftpState->data.listenConn->local.toStr(buf,MAX_IPSTRLEN),
             ftpState->data.listenConn->local.port() );

    ftpState->writeCommand(cbuf);
    ftpState->state = SENT_EPRT;
}