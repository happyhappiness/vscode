static void
ftpReadRetr(FtpStateData * ftpState)
{
    int code = ftpState->ctrl.replycode;
    debugs(9, 3, HERE);

    if (code == 125 || (code == 150 && ftpState->data.host)) {
        /* Begin data transfer */
        debugs(9, 3, HERE << "reading data channel");
        /* XXX what about Config.Timeout.read? */
        ftpState->maybeReadVirginBody();
        ftpState->state = READING_DATA;
        /*
         * Cancel the timeout on the Control socket and establish one
         * on the data socket
         */
        AsyncCall::Pointer nullCall = NULL;
        commSetTimeout(ftpState->ctrl.fd, -1, nullCall);
    } else if (code == 150) {
        /* Accept data channel */
        typedef CommCbMemFunT<FtpStateData, CommAcceptCbParams> acceptDialer;
        AsyncCall::Pointer acceptCall = JobCallback(11, 5,
                                        acceptDialer, ftpState, FtpStateData::ftpAcceptDataConnection);
        comm_accept(ftpState->data.fd, acceptCall);
        /*
         * Cancel the timeout on the Control socket and establish one
         * on the data socket
         */
        AsyncCall::Pointer nullCall = NULL;
        commSetTimeout(ftpState->ctrl.fd, -1, nullCall);

        typedef CommCbMemFunT<FtpStateData, CommTimeoutCbParams> TimeoutDialer;
        AsyncCall::Pointer timeoutCall =  JobCallback(9, 5,
                                          TimeoutDialer, ftpState,FtpStateData::ftpTimeout);
        commSetTimeout(ftpState->data.fd, Config.Timeout.read, timeoutCall);
    } else if (code >= 300) {
        if (!ftpState->flags.try_slash_hack) {
            /* Try this as a directory missing trailing slash... */
            ftpState->hackShortcut(ftpSendCwd);
        } else {
            ftpFail(ftpState);
        }
    } else {
        ftpFail(ftpState);
    }
}