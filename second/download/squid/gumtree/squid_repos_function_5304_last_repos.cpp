bool
Ftp::Client::handleEpsvReply(Ip::Address &remoteAddr)
{
    int code = ctrl.replycode;
    char *buf;
    debugs(9, 3, status());

    if (!Comm::IsConnOpen(ctrl.conn)) {
        debugs(9, 5, "The control connection to the remote end is closed");
        return false;
    }

    if (code != 229 && code != 522) {
        if (code == 200) {
            /* handle broken servers (RFC 2428 says OK code for EPSV MUST be 229 not 200) */
            /* vsftpd for one send '200 EPSV ALL ok.' without even port info.
             * Its okay to re-send EPSV 1/2 but nothing else. */
            debugs(9, DBG_IMPORTANT, "Broken FTP Server at " << ctrl.conn->remote << ". Wrong accept code for EPSV");
        } else {
            debugs(9, 2, "EPSV not supported by remote end");
        }
        return sendPassive();
    }

    if (code == 522) {
        /* Peer responded with a list of supported methods:
         *   522 Network protocol not supported, use (1)
         *   522 Network protocol not supported, use (1,2)
         *   522 Network protocol not supported, use (2)
         * TODO: Handle the (1,2) case which may happen after EPSV ALL. Close
         * data + control without self-destructing and re-open from scratch.
         */
        debugs(9, 5, "scanning: " << ctrl.last_reply);
        buf = ctrl.last_reply;
        while (buf != NULL && *buf != '\0' && *buf != '\n' && *buf != '(')
            ++buf;
        if (buf != NULL && *buf == '\n')
            ++buf;

        if (buf == NULL || *buf == '\0') {
            /* handle broken server (RFC 2428 says MUST specify supported protocols in 522) */
            debugs(9, DBG_IMPORTANT, "Broken FTP Server at " << ctrl.conn->remote << ". 522 error missing protocol negotiation hints");
            return sendPassive();
        } else if (strcmp(buf, "(1)") == 0) {
            state = SENT_EPSV_2; /* simulate having sent and failed EPSV 2 */
            return sendPassive();
        } else if (strcmp(buf, "(2)") == 0) {
            if (Ip::EnableIpv6) {
                /* If server only supports EPSV 2 and we have already tried that. Go straight to EPRT */
                if (state == SENT_EPSV_2) {
                    return sendEprt();
                } else {
                    /* or try the next Passive mode down the chain. */
                    return sendPassive();
                }
            } else {
                /* Server only accept EPSV in IPv6 traffic. */
                state = SENT_EPSV_1; /* simulate having sent and failed EPSV 1 */
                return sendPassive();
            }
        } else {
            /* handle broken server (RFC 2428 says MUST specify supported protocols in 522) */
            debugs(9, DBG_IMPORTANT, "WARNING: Server at " << ctrl.conn->remote << " sent unknown protocol negotiation hint: " << buf);
            return sendPassive();
        }
        /* coverity[unreachable] */
        /* safeguard against possible future bugs in above conditions */
        failed(ERR_FTP_FAILURE, 0);
        return false;
    }

    /*  229 Entering Extended Passive Mode (|||port|) */
    /*  ANSI sez [^0-9] is undefined, it breaks on Watcom cc */
    debugs(9, 5, "scanning: " << ctrl.last_reply);

    buf = ctrl.last_reply + strcspn(ctrl.last_reply, "(");

    char h1, h2, h3, h4;
    unsigned short port;
    int n = sscanf(buf, "(%c%c%c%hu%c)", &h1, &h2, &h3, &port, &h4);

    if (n < 4 || h1 != h2 || h1 != h3 || h1 != h4) {
        debugs(9, DBG_IMPORTANT, "Invalid EPSV reply from " <<
               ctrl.conn->remote << ": " <<
               ctrl.last_reply);

        return sendPassive();
    }

    if (0 == port) {
        debugs(9, DBG_IMPORTANT, "Unsafe EPSV reply from " <<
               ctrl.conn->remote << ": " <<
               ctrl.last_reply);

        return sendPassive();
    }

    if (Config.Ftp.sanitycheck) {
        if (port < 1024) {
            debugs(9, DBG_IMPORTANT, "Unsafe EPSV reply from " <<
                   ctrl.conn->remote << ": " <<
                   ctrl.last_reply);

            return sendPassive();
        }
    }

    remoteAddr = ctrl.conn->remote;
    remoteAddr.port(port);
    data.addr(remoteAddr);
    return true;
}