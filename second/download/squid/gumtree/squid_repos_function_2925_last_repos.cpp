void
clientReplyContext::purgeDoPurgeHead(StoreEntry *newEntry)
{
    if (newEntry && !newEntry->isNull()) {
        debugs(88, 4, "HEAD " << newEntry->url());
#if USE_HTCP
        neighborsHtcpClear(newEntry, NULL, http->request, HttpRequestMethod(Http::METHOD_HEAD), HTCP_CLR_PURGE);
#endif
        newEntry->release();
        purgeStatus = Http::scOkay;
    }

    /* And for Vary, release the base URI if none of the headers was included in the request */
    if (!http->request->vary_headers.isEmpty()
            && http->request->vary_headers.find('=') != SBuf::npos) {
        // XXX: performance regression, c_str() reallocates
        SBuf tmp(http->request->effectiveRequestUri());
        StoreEntry *entry = storeGetPublic(tmp.c_str(), Http::METHOD_GET);

        if (entry) {
            debugs(88, 4, "Vary GET " << entry->url());
#if USE_HTCP
            neighborsHtcpClear(entry, NULL, http->request, HttpRequestMethod(Http::METHOD_GET), HTCP_CLR_PURGE);
#endif
            entry->release();
            purgeStatus = Http::scOkay;
        }

        entry = storeGetPublic(tmp.c_str(), Http::METHOD_HEAD);

        if (entry) {
            debugs(88, 4, "Vary HEAD " << entry->url());
#if USE_HTCP
            neighborsHtcpClear(entry, NULL, http->request, HttpRequestMethod(Http::METHOD_HEAD), HTCP_CLR_PURGE);
#endif
            entry->release();
            purgeStatus = Http::scOkay;
        }
    }

    /*
     * Make a new entry to hold the reply to be written
     * to the client.
     */
    /* FIXME: This doesn't need to go through the store. Simply
     * push down the client chain
     */
    createStoreEntry(http->request->method, RequestFlags());

    triggerInitialStoreRead();

    HttpReply *rep = new HttpReply;
    rep->setHeaders(purgeStatus, NULL, NULL, 0, 0, -1);
    http->storeEntry()->replaceHttpReply(rep);
    http->storeEntry()->complete();
}