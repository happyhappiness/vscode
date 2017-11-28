static void
ftpSendPassive(Ftp::Gateway * ftpState)
{
    /** Checks the server control channel is still available before running. */
    if (!ftpState || !ftpState->haveControlChannel("ftpSendPassive"))
        return;

    debugs(9, 3, HERE);

    /** \par
      * Checks for 'HEAD' method request and passes off for special handling by Ftp::Gateway::processHeadResponse(). */
    if (ftpState->request->method == Http::METHOD_HEAD && (ftpState->flags.isdir || ftpState->theSize != -1)) {
        ftpState->processHeadResponse(); // may call serverComplete
        return;
    }

    if (ftpState->sendPassive()) {
        // SENT_EPSV_ALL blocks other non-EPSV connections being attempted
        if (ftpState->state == Ftp::Client::SENT_EPSV_ALL)
            ftpState->flags.epsv_all_sent = true;
    }
}