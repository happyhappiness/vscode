void
ClientHttpRequest::noteAdaptationAclCheckDone(Adaptation::ServiceGroupPointer g)
{
    debugs(93,3,HERE << this << " adaptationAclCheckDone called");

#if ICAP_CLIENT
    Adaptation::Icap::History::Pointer ih = request->icapHistory();
    if (ih != NULL) {
        if (getConn() != NULL && getConn()->clientConnection != NULL) {
            ih->rfc931 = getConn()->clientConnection->rfc931;
#if USE_OPENSSL
            if (getConn()->clientConnection->isOpen()) {
                ih->ssluser = sslGetUserEmail(fd_table[getConn()->clientConnection->fd].ssl.get());
            }
#endif
        }
        ih->log_uri = log_uri;
        ih->req_sz = req_sz;
    }
#endif

    if (!g) {
        debugs(85,3, HERE << "no adaptation needed");
        doCallouts();
        return;
    }

    startAdaptation(g);
}