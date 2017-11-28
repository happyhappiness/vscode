void
FtpStateData::scheduleReadControlReply(int buffered_ok)
{
    debugs(9, 3, HERE << ctrl.conn);

    if (buffered_ok && ctrl.offset > 0) {
        /* We've already read some reply data */
        handleControlReply();
    } else {
        /*
         * Cancel the timeout on the Data socket (if any) and
         * establish one on the control socket.
         */
        if (Comm::IsConnOpen(data.conn)) {
            commUnsetConnTimeout(data.conn);
        }

        typedef CommCbMemFunT<FtpStateData, CommTimeoutCbParams> TimeoutDialer;
        AsyncCall::Pointer timeoutCall = JobCallback(9, 5, TimeoutDialer, this, FtpStateData::ftpTimeout);
        commSetConnTimeout(ctrl.conn, Config.Timeout.read, timeoutCall);

        typedef CommCbMemFunT<FtpStateData, CommIoCbParams> Dialer;
        AsyncCall::Pointer reader = JobCallback(9, 5, Dialer, this, FtpStateData::ftpReadControlReply);
        comm_read(ctrl.conn, ctrl.buf + ctrl.offset, ctrl.size - ctrl.offset, reader);
    }
}