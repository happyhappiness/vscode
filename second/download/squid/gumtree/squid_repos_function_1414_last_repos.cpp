void
helper_server::requestTimeout(const CommTimeoutCbParams &io)
{
    debugs(26, 3, HERE << io.conn);
    helper_server *srv = static_cast<helper_server *>(io.data);

    if (!cbdataReferenceValid(srv))
        return;

    srv->checkForTimedOutRequests(srv->parent->retryTimedOut);

    debugs(84, 3, HERE << io.conn << " establish new helper_server::requestTimeout");
    AsyncCall::Pointer timeoutCall = commCbCall(84, 4, "helper_server::requestTimeout",
                                     CommTimeoutCbPtrFun(helper_server::requestTimeout, srv));

    const int timeSpent = srv->requests.empty() ? 0 : (squid_curtime - srv->requests.front()->request.dispatch_time.tv_sec);
    const int timeLeft = max(1, (static_cast<int>(srv->parent->timeout) - timeSpent));

    commSetConnTimeout(io.conn, timeLeft, timeoutCall);
}