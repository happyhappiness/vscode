void
clientReplyContext::processMiss()
{
    char *url = http->uri;
    HttpRequest *r = http->request;
    ErrorState *err = NULL;
    debugs(88, 4, "clientProcessMiss: '" << RequestMethodStr(r->method) << " " << url << "'");

    /**
     * We might have a left-over StoreEntry from a failed cache hit
     * or IMS request.
     */
    if (http->storeEntry()) {
        if (EBIT_TEST(http->storeEntry()->flags, ENTRY_SPECIAL)) {
            debugs(88, DBG_CRITICAL, "clientProcessMiss: miss on a special object (" << url << ").");
            debugs(88, DBG_CRITICAL, "\tlog_type = " << Format::log_tags[http->logType]);
            http->storeEntry()->dump(1);
        }

        removeClientStoreReference(&sc, http);
    }

    /** Check if its a PURGE request to be actioned. */
    if (r->method == METHOD_PURGE) {
        purgeRequest();
        return;
    }

    /** Check if its an 'OTHER' request. Purge all cached entries if so and continue. */
    if (r->method == METHOD_OTHER) {
        purgeAllCached();
    }

    /** Check if 'only-if-cached' flag is set. Action if so. */
    if (http->onlyIfCached()) {
        processOnlyIfCachedMiss();
        return;
    }

    /// Deny loops
    if (r->flags.loopDetected) {
        http->al->http.code = HTTP_FORBIDDEN;
        err = clientBuildError(ERR_ACCESS_DENIED, HTTP_FORBIDDEN, NULL, http->getConn()->clientConnection->remote, http->request);
        createStoreEntry(r->method, RequestFlags());
        errorAppendEntry(http->storeEntry(), err);
        triggerInitialStoreRead();
        return;
    } else {
        assert(http->out.offset == 0);
        createStoreEntry(r->method, r->flags);
        triggerInitialStoreRead();

        if (http->redirect.status) {
            HttpReply *rep = new HttpReply;
            http->logType = LOG_TCP_REDIRECT;
            http->storeEntry()->releaseRequest();
            rep->redirect(http->redirect.status, http->redirect.location);
            http->storeEntry()->replaceHttpReply(rep);
            http->storeEntry()->complete();
            return;
        }

        /** Check for internal requests. Update Protocol info if so. */
        if (http->flags.internal)
            r->protocol = AnyP::PROTO_INTERNAL;

        assert(r->clientConnectionManager == http->getConn());

        /** Start forwarding to get the new object from network */
        Comm::ConnectionPointer conn = http->getConn() != NULL ? http->getConn()->clientConnection : NULL;
        FwdState::Start(conn, http->storeEntry(), r, http->al);
    }
}