void
Ftp::Client::scheduleReadControlReply(int buffered_ok)
{
    debugs(9, 3, ctrl.conn);

    if (buffered_ok && ctrl.offset > 0) {
        /* We've already read some reply data */
        handleControlReply();
    } else {

        if (!Comm::IsConnOpen(ctrl.conn)) {
            debugs(9, 3, "cannot read without ctrl " << ctrl.conn);
            return;
        }
        /*
         * Cancel the timeout on the Data socket (if any) and
         * establish one on the control socket.
         */
        if (Comm::IsConnOpen(data.conn)) {
            commUnsetConnTimeout(data.conn);
        }

        const time_t tout = shortenReadTimeout ?
                            min(Config.Timeout.connect, Config.Timeout.read):
                            Config.Timeout.read;
        shortenReadTimeout = false; // we only need to do this once, after PASV

        typedef CommCbMemFunT<Client, CommTimeoutCbParams> TimeoutDialer;
        AsyncCall::Pointer timeoutCall = JobCallback(9, 5, TimeoutDialer, this, Ftp::Client::timeout);
        commSetConnTimeout(ctrl.conn, tout, timeoutCall);

        typedef CommCbMemFunT<Client, CommIoCbParams> Dialer;
        AsyncCall::Pointer reader = JobCallback(9, 5, Dialer, this, Ftp::Client::readControlReply);
        comm_read(ctrl.conn, ctrl.buf + ctrl.offset, ctrl.size - ctrl.offset, reader);
    }
}