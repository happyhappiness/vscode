void FtpStateData::readStor()
{
    int code = ctrl.replycode;
    debugs(9, 3, HERE);

    if (code == 125 || (code == 150 && data.host)) {
        if (!startRequestBodyFlow()) { // register to receive body data
            ftpFail(this);
            return;
        }

        /*\par
         * When client status is 125, or 150 without a hostname, Begin data transfer. */
        debugs(9, 3, HERE << "starting data transfer");
        sendMoreRequestBody();
        /** \par
         * Cancel the timeout on the Control socket and
         * establish one on the data socket.
         */
        AsyncCall::Pointer nullCall = NULL;
        commSetTimeout(ctrl.fd, -1, nullCall);

        typedef CommCbMemFunT<FtpStateData, CommTimeoutCbParams> TimeoutDialer;
        AsyncCall::Pointer timeoutCall =  JobCallback(9, 5,
                                          TimeoutDialer, this, FtpStateData::ftpTimeout);

        commSetTimeout(data.fd, Config.Timeout.read, timeoutCall);

        state = WRITING_DATA;
        debugs(9, 3, HERE << "writing data channel");
    } else if (code == 150) {
        /*\par
         * When client code is 150 with a hostname, Accept data channel. */
        debugs(9, 3, "ftpReadStor: accepting data channel");
        typedef CommCbMemFunT<FtpStateData, CommAcceptCbParams> acceptDialer;
        AsyncCall::Pointer acceptCall = JobCallback(11, 5,
                                        acceptDialer, this, FtpStateData::ftpAcceptDataConnection);

        comm_accept(data.fd, acceptCall);
    } else {
        debugs(9, DBG_IMPORTANT, HERE << "Unexpected reply code "<< std::setfill('0') << std::setw(3) << code);
        ftpFail(this);
    }
}