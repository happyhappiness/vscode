void
ClientRequestContext::sslBumpAccessCheckDone(const allow_t &answer)
{
    if (!httpStateIsValid())
        return;

    const Ssl::BumpMode bumpMode = answer.allowed() ?
                                   static_cast<Ssl::BumpMode>(answer.kind) : Ssl::bumpSplice;
    http->sslBumpNeed(bumpMode); // for processRequest() to bump if needed
    http->al->ssl.bumpMode = bumpMode; // for logging

    if (bumpMode == Ssl::bumpTerminate) {
        const Comm::ConnectionPointer clientConn = http->getConn() ? http->getConn()->clientConnection : nullptr;
        if (Comm::IsConnOpen(clientConn)) {
            debugs(85, 3, "closing after Ssl::bumpTerminate ");
            clientConn->close();
        }
        return;
    }

    http->doCallouts();
}