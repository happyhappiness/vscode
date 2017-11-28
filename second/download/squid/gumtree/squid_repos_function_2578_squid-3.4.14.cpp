static void
ftpSendPassive(FtpStateData * ftpState)
{
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
    if (ftpState->request->method == Http::METHOD_HEAD && (ftpState->flags.isdir || ftpState->theSize != -1)) {
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
        if (ftpState->ctrl.conn->local.isIPv6()) {
            debugs(9, 5, HERE << "FTP Channel is IPv6 (" << ftpState->ctrl.conn->remote << ") attempting EPSV 2 after EPSV ALL has failed.");
            snprintf(cbuf, CTRL_BUFLEN, "EPSV 2\r\n");
            ftpState->state = SENT_EPSV_2;
            break;
        }
        // else fall through to skip EPSV 2

    case SENT_EPSV_2: /* EPSV IPv6 failed. Try EPSV IPv4 */
        if (ftpState->ctrl.conn->local.isIPv4()) {
            debugs(9, 5, HERE << "FTP Channel is IPv4 (" << ftpState->ctrl.conn->remote << ") attempting EPSV 1 after EPSV ALL has failed.");
            snprintf(cbuf, CTRL_BUFLEN, "EPSV 1\r\n");
            ftpState->state = SENT_EPSV_1;
            break;
        } else if (ftpState->flags.epsv_all_sent) {
            debugs(9, DBG_IMPORTANT, "FTP does not allow PASV method after 'EPSV ALL' has been sent.");
            ftpFail(ftpState);
            return;
        }
        // else fall through to skip EPSV 1

    case SENT_EPSV_1: /* EPSV options exhausted. Try PASV now. */
        debugs(9, 5, HERE << "FTP Channel (" << ftpState->ctrl.conn->remote << ") rejects EPSV connection attempts. Trying PASV instead.");
        snprintf(cbuf, CTRL_BUFLEN, "PASV\r\n");
        ftpState->state = SENT_PASV;
        break;

    default:
        if (!Config.Ftp.epsv) {
            debugs(9, 5, HERE << "EPSV support manually disabled. Sending PASV for FTP Channel (" << ftpState->ctrl.conn->remote <<")");
            snprintf(cbuf, CTRL_BUFLEN, "PASV\r\n");
            ftpState->state = SENT_PASV;
        } else if (Config.Ftp.epsv_all) {
            debugs(9, 5, HERE << "EPSV ALL manually enabled. Attempting with FTP Channel (" << ftpState->ctrl.conn->remote <<")");
            snprintf(cbuf, CTRL_BUFLEN, "EPSV ALL\r\n");
            ftpState->state = SENT_EPSV_ALL;
            /* block other non-EPSV connections being attempted */
            ftpState->flags.epsv_all_sent = true;
        } else {
            if (ftpState->ctrl.conn->local.isIPv6()) {
                debugs(9, 5, HERE << "FTP Channel (" << ftpState->ctrl.conn->remote << "). Sending default EPSV 2");
                snprintf(cbuf, CTRL_BUFLEN, "EPSV 2\r\n");
                ftpState->state = SENT_EPSV_2;
            }
            if (ftpState->ctrl.conn->local.isIPv4()) {
                debugs(9, 5, HERE << "Channel (" << ftpState->ctrl.conn->remote <<"). Sending default EPSV 1");
                snprintf(cbuf, CTRL_BUFLEN, "EPSV 1\r\n");
                ftpState->state = SENT_EPSV_1;
            }
        }
        break;
    }

    ftpState->writeCommand(cbuf);

    /*
     * ugly hack for ftp servers like ftp.netscape.com that sometimes
     * dont acknowledge PASV commands. Use connect timeout to be faster then read timeout (minutes).
     */
    typedef CommCbMemFunT<FtpStateData, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall =  JobCallback(9, 5,
                                      TimeoutDialer, ftpState, FtpStateData::ftpTimeout);
    commSetConnTimeout(ftpState->ctrl.conn, Config.Timeout.connect, timeoutCall);
}