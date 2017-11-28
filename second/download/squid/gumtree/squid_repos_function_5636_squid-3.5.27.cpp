bool
Comm::ConnOpener::createFd()
{
    Must(temporaryFd_ < 0);

    // our initators signal abort by cancelling their callbacks
    if (callback_ == NULL || callback_->canceled())
        return false;

    temporaryFd_ = comm_openex(SOCK_STREAM, IPPROTO_TCP, conn_->local, conn_->flags, host_);
    if (temporaryFd_ < 0) {
        sendAnswer(Comm::ERR_CONNECT, 0, "Comm::ConnOpener::createFd");
        return false;
    }

    // Set TOS if needed.
    if (conn_->tos &&
            Ip::Qos::setSockTos(temporaryFd_, conn_->tos, conn_->remote.isIPv4() ? AF_INET : AF_INET6) < 0)
        conn_->tos = 0;
#if SO_MARK
    if (conn_->nfmark &&
            Ip::Qos::setSockNfmark(temporaryFd_, conn_->nfmark) < 0)
        conn_->nfmark = 0;
#endif

    fd_table[temporaryFd_].tosToServer = conn_->tos;
    fd_table[temporaryFd_].nfmarkToServer = conn_->nfmark;

    typedef CommCbMemFunT<Comm::ConnOpener, CommCloseCbParams> abortDialer;
    calls_.earlyAbort_ = JobCallback(5, 4, abortDialer, this, Comm::ConnOpener::earlyAbort);
    comm_add_close_handler(temporaryFd_, calls_.earlyAbort_);

    typedef CommCbMemFunT<Comm::ConnOpener, CommTimeoutCbParams> timeoutDialer;
    calls_.timeout_ = JobCallback(5, 4, timeoutDialer, this, Comm::ConnOpener::timeout);
    debugs(5, 3, conn_ << " will timeout in " << (deadline_ - squid_curtime));

    // Update the fd_table directly because commSetConnTimeout() needs open conn_
    assert(temporaryFd_ < Squid_MaxFD);
    assert(fd_table[temporaryFd_].flags.open);
    typedef CommTimeoutCbParams Params;
    Params &params = GetCommParams<Params>(calls_.timeout_);
    params.conn = conn_;
    fd_table[temporaryFd_].timeoutHandler = calls_.timeout_;
    fd_table[temporaryFd_].timeout = deadline_;

    return true;
}