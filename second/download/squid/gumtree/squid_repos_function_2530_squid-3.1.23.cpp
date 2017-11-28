void
FtpStateData::scheduleReadControlReply(int buffered_ok)
{
    debugs(9, 3, HERE << "FD " << ctrl.fd);

    if (buffered_ok && ctrl.offset > 0) {
        /* We've already read some reply data */
        handleControlReply();
    } else {
        /* XXX What about Config.Timeout.read? */
        typedef CommCbMemFunT<FtpStateData, CommIoCbParams> Dialer;
        AsyncCall::Pointer reader = JobCallback(9, 5,
                                                Dialer, this, FtpStateData::ftpReadControlReply);
        comm_read(ctrl.fd, ctrl.buf + ctrl.offset, ctrl.size - ctrl.offset, reader);
        /*
         * Cancel the timeout on the Data socket (if any) and
         * establish one on the control socket.
         */

        if (data.fd > -1) {
            AsyncCall::Pointer nullCall =  NULL;
            commSetTimeout(data.fd, -1, nullCall);
        }

        typedef CommCbMemFunT<FtpStateData, CommTimeoutCbParams> TimeoutDialer;
        AsyncCall::Pointer timeoutCall = JobCallback(9, 5,
                                         TimeoutDialer, this, FtpStateData::ftpTimeout);

        commSetTimeout(ctrl.fd, Config.Timeout.read, timeoutCall);
    }
}