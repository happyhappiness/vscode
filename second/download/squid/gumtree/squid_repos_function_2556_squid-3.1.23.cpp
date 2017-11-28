static void
ftpReadPasv(FtpStateData * ftpState)
{
    int code = ftpState->ctrl.replycode;
    int h1, h2, h3, h4;
    int p1, p2;
    int n;
    unsigned short port;
    IpAddress ipa_remote;
    int fd = ftpState->data.fd;
    char *buf;
    LOCAL_ARRAY(char, ipaddr, 1024);
    debugs(9, 3, HERE);

    if (code != 227) {
        debugs(9, 2, "PASV not supported by remote end");
        ftpSendEPRT(ftpState);
        return;
    }

    /*  227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).  */
    /*  ANSI sez [^0-9] is undefined, it breaks on Watcom cc */
    debugs(9, 5, HERE << "scanning: " << ftpState->ctrl.last_reply);

    buf = ftpState->ctrl.last_reply + strcspn(ftpState->ctrl.last_reply, "0123456789");

    n = sscanf(buf, "%d,%d,%d,%d,%d,%d", &h1, &h2, &h3, &h4, &p1, &p2);

    if (n != 6 || p1 < 0 || p2 < 0 || p1 > 255 || p2 > 255) {
        debugs(9, DBG_IMPORTANT, "Unsafe PASV reply from " <<
               fd_table[ftpState->ctrl.fd].ipaddr << ": " <<
               ftpState->ctrl.last_reply);

        ftpSendEPRT(ftpState);
        return;
    }

    snprintf(ipaddr, 1024, "%d.%d.%d.%d", h1, h2, h3, h4);

    ipa_remote = ipaddr;

    if ( ipa_remote.IsAnyAddr() ) {
        debugs(9, DBG_IMPORTANT, "Unsafe PASV reply from " <<
               fd_table[ftpState->ctrl.fd].ipaddr << ": " <<
               ftpState->ctrl.last_reply);

        ftpSendEPRT(ftpState);
        return;
    }

    port = ((p1 << 8) + p2);

    if (0 == port) {
        debugs(9, DBG_IMPORTANT, "Unsafe PASV reply from " <<
               fd_table[ftpState->ctrl.fd].ipaddr << ": " <<
               ftpState->ctrl.last_reply);

        ftpSendEPRT(ftpState);
        return;
    }

    if (Config.Ftp.sanitycheck) {
        if (port < 1024) {
            debugs(9, DBG_IMPORTANT, "Unsafe PASV reply from " <<
                   fd_table[ftpState->ctrl.fd].ipaddr << ": " <<
                   ftpState->ctrl.last_reply);

            ftpSendEPRT(ftpState);
            return;
        }
    }

    ftpState->data.port = port;

    safe_free(ftpState->data.host);
    if (Config.Ftp.sanitycheck)
        ftpState->data.host = xstrdup(fd_table[ftpState->ctrl.fd].ipaddr);
    else
        ftpState->data.host = xstrdup(ipaddr);

    safe_free(ftpState->ctrl.last_command);

    safe_free(ftpState->ctrl.last_reply);

    ftpState->ctrl.last_command = xstrdup("Connect to server data port");

    debugs(9, 3, HERE << "connecting to " << ftpState->data.host << ", port " << ftpState->data.port);

    commConnectStart(fd, ipaddr, port, FtpStateData::ftpPasvCallback, ftpState);
}