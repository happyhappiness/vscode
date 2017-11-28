void
clientReplyContext::processExpired()
{
    const char *url = storeId();
    debugs(88, 3, "clientReplyContext::processExpired: '" << http->uri << "'");
    const time_t lastmod = http->storeEntry()->lastModified();
    assert(lastmod >= 0);
    /*
     * check if we are allowed to contact other servers
     * @?@: Instead of a 504 (Gateway Timeout) reply, we may want to return
     *      a stale entry *if* it matches client requirements
     */

    if (http->onlyIfCached()) {
        processOnlyIfCachedMiss();
        return;
    }

    http->request->flags.refresh = true;
#if STORE_CLIENT_LIST_DEBUG
    /* Prevent a race with the store client memory free routines
     */
    assert(storeClientIsThisAClient(sc, this));
#endif
    /* Prepare to make a new temporary request */
    saveState();

    // TODO: support collapsed revalidation of Vary-controlled entries
    const bool collapsingAllowed = Config.onoff.collapsed_forwarding &&
                                   !Store::Root().smpAware() &&
                                   http->request->vary_headers.isEmpty();

    StoreEntry *entry = nullptr;
    if (collapsingAllowed) {
        if ((entry = storeGetPublicByRequest(http->request, ksRevalidation)))
            entry->lock("clientReplyContext::processExpired#alreadyRevalidating");
    }

    if (entry) {
        debugs(88, 5, "collapsed on existing revalidation entry: " << *entry);
        collapsedRevalidation = crSlave;
    } else {
        entry = storeCreateEntry(url,
                                 http->log_uri, http->request->flags, http->request->method);
        /* NOTE, don't call StoreEntry->lock(), storeCreateEntry() does it */

        if (collapsingAllowed) {
            debugs(88, 5, "allow other revalidation requests to collapse on " << *entry);
            Store::Root().allowCollapsing(entry, http->request->flags,
                                          http->request->method);
            collapsedRevalidation = crInitiator;
        } else {
            collapsedRevalidation = crNone;
        }
    }

    sc = storeClientListAdd(entry, this);
#if USE_DELAY_POOLS
    /* delay_id is already set on original store client */
    sc->setDelayId(DelayId::DelayClient(http));
#endif

    http->request->lastmod = lastmod;

    if (!http->request->header.has(HDR_IF_NONE_MATCH)) {
        ETag etag = {NULL, -1}; // TODO: make that a default ETag constructor
        if (old_entry->hasEtag(etag) && !etag.weak)
            http->request->etag = etag.str;
    }

    debugs(88, 5, "lastmod " << entry->lastModified());
    http->storeEntry(entry);
    assert(http->out.offset == 0);
    assert(http->request->clientConnectionManager == http->getConn());

    if (collapsedRevalidation != crSlave) {
        /*
         * A refcounted pointer so that FwdState stays around as long as
         * this clientReplyContext does
         */
        Comm::ConnectionPointer conn = http->getConn() != NULL ? http->getConn()->clientConnection : NULL;
        FwdState::Start(conn, http->storeEntry(), http->request, http->al);
    }

    /* Register with storage manager to receive updates when data comes in. */

    if (EBIT_TEST(entry->flags, ENTRY_ABORTED))
        debugs(88, DBG_CRITICAL, "clientReplyContext::processExpired: Found ENTRY_ABORTED object");

    {
        /* start counting the length from 0 */
        StoreIOBuffer localTempBuffer(HTTP_REQBUF_SZ, 0, tempbuf);
        storeClientCopy(sc, entry, localTempBuffer, HandleIMSReply, this);
    }
}