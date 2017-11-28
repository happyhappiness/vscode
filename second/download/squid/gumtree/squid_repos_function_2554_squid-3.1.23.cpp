static void
ftpSendPassive(FtpStateData * ftpState)
{
    IpAddress addr;
    struct addrinfo *AI = NULL;

    /** Checks the server control channel is still available before running. */
    if (!ftpState || !ftpState->haveControlChannel("ftpSendPassive"))
        return;

    debugs(9, 3, HERE);

    /** \par
      * Checks for EPSV ALL special conditions:
      * If enabled to be sent, squid MUST NOT request any other connect methods.
      * If 'ALL' is sent and fails the entire FTP Session fails.
      * NP: By my reading exact EPSV protocols maybe attempted, but only EPSV method. */
    if (Config.Ftp.epsv_all && ftpState->flags.epsv_all_sent && ftpState->state == SENT_EPSV_1 ) {
        debugs(9, DBG_IMPORTANT, "FTP does not allow PASV method after 'EPSV ALL' has been sent.");
        ftpFail(ftpState);
        return;
    }

    /** \par
      * Checks for 'HEAD' method request and passes off for special handling by FtpStateData::processHeadResponse(). */
    if (ftpState->request->method == METHOD_HEAD && (ftpState->flags.isdir || ftpState->theSize != -1)) {
        ftpState->processHeadResponse(); // may call serverComplete
        return;
    }

    /// Closes any old FTP-Data connection which may exist. */
    ftpState->data.close();

    /** \par
      * Checks for previous EPSV/PASV failures on this server/session.
      * Diverts to EPRT immediately if they are not working. */
    if (!ftpState->flags.pasv_supported) {
        ftpSendEPRT(ftpState);
        return;
    }

    /** \par
      * Locates the Address of the remote server. */
    addr.InitAddrInfo(AI);

    if (getsockname(ftpState->ctrl.fd, AI->ai_addr, &AI->ai_addrlen)) {
        /** If it cannot be located the FTP Session is killed. */
        addr.FreeAddrInfo(AI);
        debugs(9, DBG_CRITICAL, HERE << "getsockname(" << ftpState->ctrl.fd << ",'" << addr << "',...): " << xstrerror());
        ftpFail(ftpState);
        return;
    }

    addr = *AI;
    addr.FreeAddrInfo(AI);

    /** \par
      * Send EPSV (ALL,2,1) or PASV on the control channel.
      *
      *  - EPSV ALL  is used if enabled.
      *  - EPSV 2    is used if ALL is disabled and IPv6 is available and ctrl channel is IPv6.
      *  - EPSV 1    is used if EPSV 2 (IPv6) fails or is not available or ctrl channel is IPv4.
      *  - PASV      is used if EPSV 1 fails.
      */
    switch (ftpState->state) {
    case SENT_EPSV_ALL: /* EPSV ALL resulted in a bad response. Try ther EPSV methods. */
        ftpState->flags.epsv_all_sent = true;
        if (addr.IsIPv6()) {
            debugs(9, 5, HERE << "FTP Channel is IPv6 (" << addr << ") attempting EPSV 2 after EPSV ALL has failed.");
            snprintf(cbuf, 1024, "EPSV 2\r\n");
            ftpState->state = SENT_EPSV_2;
            break;
        }
        // else fall through to skip EPSV 2

    case SENT_EPSV_2: /* EPSV IPv6 failed. Try EPSV IPv4 */
        if (addr.IsIPv4()) {
            debugs(9, 5, HERE << "FTP Channel is IPv4 (" << addr << ") attempting EPSV 1 after EPSV ALL has failed.");
            snprintf(cbuf, 1024, "EPSV 1\r\n");
            ftpState->state = SENT_EPSV_1;
            break;
        } else if (ftpState->flags.epsv_all_sent) {
            debugs(9, DBG_IMPORTANT, "FTP does not allow PASV method after 'EPSV ALL' has been sent.");
            ftpFail(ftpState);
            return;
        }
        // else fall through to skip EPSV 1

    case SENT_EPSV_1: /* EPSV options exhausted. Try PASV now. */
        debugs(9, 5, HERE << "FTP Channel (" << addr << ") rejects EPSV connection attempts. Trying PASV instead.");
        snprintf(cbuf, 1024, "PASV\r\n");
        ftpState->state = SENT_PASV;
        break;

    default:
        if (!Config.Ftp.epsv) {
            debugs(9, 5, HERE << "EPSV support manually disabled. Sending PASV for FTP Channel (" << addr <<")");
            snprintf(cbuf, 1024, "PASV\r\n");
            ftpState->state = SENT_PASV;
        } else if (Config.Ftp.epsv_all) {
            debugs(9, 5, HERE << "EPSV ALL manually enabled. Attempting with FTP Channel (" << addr <<")");
            snprintf(cbuf, 1024, "EPSV ALL\r\n");
            ftpState->state = SENT_EPSV_ALL;
            /* block other non-EPSV connections being attempted */
            ftpState->flags.epsv_all_sent = true;
        } else {
            if (addr.IsIPv6()) {
                debugs(9, 5, HERE << "FTP Channel (" << addr << "). Sending default EPSV 2");
                snprintf(cbuf, 1024, "EPSV 2\r\n");
                ftpState->state = SENT_EPSV_2;
            }
            if (addr.IsIPv4()) {
                debugs(9, 5, HERE << "Channel (" << addr <<"). Sending default EPSV 1");
                snprintf(cbuf, 1024, "EPSV 1\r\n");
                ftpState->state = SENT_EPSV_1;
            }
        }
        break;
    }

    /** Otherwise, Open data channel with the same local address as control channel (on a new random port!) */
    addr.SetPort(0);
    int fd = comm_open(SOCK_STREAM,
                       IPPROTO_TCP,
                       addr,
                       COMM_NONBLOCKING,
                       ftpState->entry->url());

    debugs(9, 3, HERE << "Unconnected data socket created on FD " << fd << " from " << addr);

    if (fd < 0) {
        ftpFail(ftpState);
        return;
    }

    ftpState->data.opened(fd, ftpState->dataCloser());
    ftpState->writeCommand(cbuf);

    /*
     * ugly hack for ftp servers like ftp.netscape.com that sometimes
     * dont acknowledge PASV commands.
     */
    typedef CommCbMemFunT<FtpStateData, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall =  JobCallback(9, 5,
                                      TimeoutDialer, ftpState, FtpStateData::ftpTimeout);

    commSetTimeout(ftpState->data.fd, 15, timeoutCall);
}