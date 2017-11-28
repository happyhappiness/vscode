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
            debugs(88, 0, "clientProcessMiss: miss on a special object (" << url << ").");
            debugs(88, 0, "\tlog_type = " << log_tags[http->logType]);
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

    /// Deny loops for accelerator and interceptor. TODO: deny in all modes?
    if (r->flags.loopdetect &&
            (http->flags.accel || http->flags.intercepted)) {
        http->al.http.code = HTTP_FORBIDDEN;
        err = clientBuildError(ERR_ACCESS_DENIED, HTTP_FORBIDDEN, NULL, http->getConn()->peer, http->request);
        createStoreEntry(r->method, request_flags());
        errorAppendEntry(http->storeEntry(), err);
        triggerInitialStoreRead();
        return;
    } else {
        assert(http->out.offset == 0);
        createStoreEntry(r->method, r->flags);
        triggerInitialStoreRead();

        if (http->redirect.status) {
            HttpReply *rep = new HttpReply;
#if LOG_TCP_REDIRECTS

            http->logType = LOG_TCP_REDIRECT;
#endif

            http->storeEntry()->releaseRequest();
            rep->redirect(http->redirect.status, http->redirect.location);
            http->storeEntry()->replaceHttpReply(rep);
            http->storeEntry()->complete();
            return;
        }

        /** Check for internal requests. Update Protocol info if so. */
        if (http->flags.internal)
            r->protocol = PROTO_INTERNAL;

        /** Start forwarding to get the new object from network */
        FwdState::fwdStart(http->getConn() != NULL ? http->getConn()->fd : -1,
                           http->storeEntry(),
                           r);
    }
}