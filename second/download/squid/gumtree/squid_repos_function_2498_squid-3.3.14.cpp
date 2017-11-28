void
FtpStateData::switchTimeoutToDataChannel()
{
    commUnsetConnTimeout(ctrl.conn);

    typedef CommCbMemFunT<FtpStateData, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall = JobCallback(9, 5, TimeoutDialer, this, FtpStateData::ftpTimeout);
    commSetConnTimeout(data.conn, Config.Timeout.read, timeoutCall);
}