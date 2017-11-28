void
Log::TcpLogger::doConnect()
{
    if (shutting_down)
        return;

    debugs(MY_DEBUG_SECTION, 3, "connecting");
    Must(!conn);

    Comm::ConnectionPointer futureConn = new Comm::Connection;
    futureConn->remote = remote;
    futureConn->local.setAnyAddr();
    if (futureConn->remote.isIPv4())
        futureConn->local.setIPv4();

    typedef CommCbMemFunT<TcpLogger, CommConnectCbParams> Dialer;
    AsyncCall::Pointer call = JobCallback(MY_DEBUG_SECTION, 5, Dialer, this, Log::TcpLogger::connectDone);
    AsyncJob::Start(new Comm::ConnOpener(futureConn, call, 2));
}