static void
ftpReadEPSV(FtpStateData* ftpState)
{
    int code = ftpState->ctrl.replycode;
    Ip::Address ipa_remote;
    char *buf;
    debugs(9, 3, HERE);

    if (code != 229 && code != 522) {
        if (code == 200) {
            /* handle broken servers (RFC 2428 says OK code for EPSV MUST be 229 not 200) */
            /* vsftpd for one send '200 EPSV ALL ok.' without even port info.
             * Its okay to re-send EPSV 1/2 but nothing else. */
            debugs(9, DBG_IMPORTANT, "Broken FTP Server at " << ftpState->ctrl.conn->remote << ". Wrong accept code for EPSV");
        } else {
            debugs(9, 2, "EPSV not supported by remote end");
            ftpState->state = SENT_EPSV_1; /* simulate having failed EPSV 1 (last EPSV to try before shifting to PASV) */
        }
        ftpSendPassive(ftpState);
        return;
    }

    if (code == 522) {
        /* server response with list of supported methods   */
        /*   522 Network protocol not supported, use (1)    */
        /*   522 Network protocol not supported, use (1,2)  */
        /*   522 Network protocol not supported, use (2)  */
        /* TODO: handle the (1,2) case. We might get it back after EPSV ALL
         * which means close data + control without self-destructing and re-open from scratch. */
        debugs(9, 5, HERE << "scanning: " << ftpState->ctrl.last_reply);
        buf = ftpState->ctrl.last_reply;
        while (buf != NULL && *buf != '\0' && *buf != '\n' && *buf != '(')
            ++buf;
        if (buf != NULL && *buf == '\n')
            ++buf;

        if (buf == NULL || *buf == '\0') {
            /* handle broken server (RFC 2428 says MUST specify supported protocols in 522) */
            debugs(9, DBG_IMPORTANT, "Broken FTP Server at " << ftpState->ctrl.conn->remote << ". 522 error missing protocol negotiation hints");
            ftpSendPassive(ftpState);
        } else if (strcmp(buf, "(1)") == 0) {
            ftpState->state = SENT_EPSV_2; /* simulate having sent and failed EPSV 2 */
            ftpSendPassive(ftpState);
        } else if (strcmp(buf, "(2)") == 0) {
            if (Ip::EnableIpv6) {
                /* If server only supports EPSV 2 and we have already tried that. Go straight to EPRT */
                if (ftpState->state == SENT_EPSV_2) {
                    ftpSendEPRT(ftpState);
                } else {
                    /* or try the next Passive mode down the chain. */
                    ftpSendPassive(ftpState);
                }
            } else {
                /* Server only accept EPSV in IPv6 traffic. */
                ftpState->state = SENT_EPSV_1; /* simulate having sent and failed EPSV 1 */
                ftpSendPassive(ftpState);
            }
        } else {
            /* handle broken server (RFC 2428 says MUST specify supported protocols in 522) */
            debugs(9, DBG_IMPORTANT, "WARNING: Server at " << ftpState->ctrl.conn->remote << " sent unknown protocol negotiation hint: " << buf);
            ftpSendPassive(ftpState);
        }
        return;
    }

    /*  229 Entering Extended Passive Mode (|||port|) */
    /*  ANSI sez [^0-9] is undefined, it breaks on Watcom cc */
    debugs(9, 5, "scanning: " << ftpState->ctrl.last_reply);

    buf = ftpState->ctrl.last_reply + strcspn(ftpState->ctrl.last_reply, "(");

    char h1, h2, h3, h4;
    unsigned short port;
    int n = sscanf(buf, "(%c%c%c%hu%c)", &h1, &h2, &h3, &port, &h4);

    if (n < 4 || h1 != h2 || h1 != h3 || h1 != h4) {
        debugs(9, DBG_IMPORTANT, "Invalid EPSV reply from " <<
               ftpState->ctrl.conn->remote << ": " <<
               ftpState->ctrl.last_reply);

        ftpSendPassive(ftpState);
        return;
    }

    if (0 == port) {
        debugs(9, DBG_IMPORTANT, "Unsafe EPSV reply from " <<
               ftpState->ctrl.conn->remote << ": " <<
               ftpState->ctrl.last_reply);

        ftpSendPassive(ftpState);
        return;
    }

    if (Config.Ftp.sanitycheck) {
        if (port < 1024) {
            debugs(9, DBG_IMPORTANT, "Unsafe EPSV reply from " <<
                   ftpState->ctrl.conn->remote << ": " <<
                   ftpState->ctrl.last_reply);

            ftpSendPassive(ftpState);
            return;
        }
    }

    ftpState->data.port = port;

    safe_free(ftpState->data.host);
    ftpState->data.host = xstrdup(fd_table[ftpState->ctrl.conn->fd].ipaddr);

    safe_free(ftpState->ctrl.last_command);

    safe_free(ftpState->ctrl.last_reply);

    ftpState->ctrl.last_command = xstrdup("Connect to server data port");

    // Generate a new data channel descriptor to be opened.
    Comm::ConnectionPointer conn = new Comm::Connection;
    conn->local = ftpState->ctrl.conn->local;
    conn->local.SetPort(0);
    conn->remote = ftpState->ctrl.conn->remote;
    conn->remote.SetPort(port);

    debugs(9, 3, HERE << "connecting to " << conn->remote);

    ftpState->data.opener = commCbCall(9,3, "FtpStateData::ftpPasvCallback", CommConnectCbPtrFun(FtpStateData::ftpPasvCallback, ftpState));
    Comm::ConnOpener *cs = new Comm::ConnOpener(conn, ftpState->data.opener, Config.Timeout.connect);
    cs->setHost(ftpState->data.host);
    AsyncJob::Start(cs);
}