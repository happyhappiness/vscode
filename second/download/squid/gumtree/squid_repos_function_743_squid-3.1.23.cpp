void
ClientRequestContext::adaptationAclCheckDone(Adaptation::ServiceGroupPointer g)
{
    debugs(93,3,HERE << this << " adaptationAclCheckDone called");
    assert(http);

#if ICAP_CLIENT
    Adaptation::Icap::History::Pointer ih = http->request->icapHistory();
    if (ih != NULL) {
        if (http->getConn() != NULL) {
            ih->rfc931 = http->getConn()->rfc931;
#if USE_SSL
            ih->ssluser = sslGetUserEmail(fd_table[http->getConn()->fd].ssl);
#endif
        }
        ih->log_uri = http->log_uri;
        ih->req_sz = http->req_sz;
    }
#endif

    if (!g) {
        debugs(85,3, HERE << "no adaptation needed");
        http->doCallouts();
        return;
    }

    http->startAdaptation(g);
}