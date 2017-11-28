void
Ftp::Client::switchTimeoutToDataChannel()
{
    commUnsetConnTimeout(ctrl.conn);

    typedef CommCbMemFunT<Client, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall = JobCallback(9, 5, TimeoutDialer, this,
                                     Ftp::Client::timeout);
    commSetConnTimeout(data.conn, Config.Timeout.read, timeoutCall);
}