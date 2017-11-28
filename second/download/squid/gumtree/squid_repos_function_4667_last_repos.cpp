void
Http::One::Server::start()
{
    ConnStateData::start();

#if USE_OPENSSL
    // XXX: Until we create an HttpsServer class, use this hack to allow old
    // client_side.cc code to manipulate ConnStateData object directly
    if (isHttpsServer) {
        postHttpsAccept();
        return;
    }
#endif

    typedef CommCbMemFunT<Server, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall =  JobCallback(33, 5,
                                      TimeoutDialer, this, Http1::Server::requestTimeout);
    commSetConnTimeout(clientConnection, Config.Timeout.request_start_timeout, timeoutCall);
    readSomeData();
}