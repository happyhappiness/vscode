void
clientReplyContext::identifyFoundObject(StoreEntry *newEntry)
{
    StoreEntry *e = newEntry;
    HttpRequest *r = http->request;

    /** \li If the entry received isNull() then we ignore it. */
    if (e->isNull()) {
        http->storeEntry(NULL);
    } else {
        http->storeEntry(e);
    }

    e = http->storeEntry();

    /* Release IP-cache entries on reload */
    /** \li If the request has no-cache flag set or some no_cache HACK in operation we
      * 'invalidate' the cached IP entries for this request ???
      */
    if (r->flags.noCache) {

#if USE_DNSHELPER
        ipcacheInvalidate(r->GetHost());
#else
        ipcacheInvalidateNegative(r->GetHost());
#endif /* USE_DNSHELPER */

    } else if (r->flags.noCacheHack()) {

#if USE_DNSHELPER
        ipcacheInvalidate(r->GetHost());
#else
        ipcacheInvalidateNegative(r->GetHost());
#endif /* USE_DNSHELPER */

    }

#if USE_CACHE_DIGESTS
    lookup_type = http->storeEntry() ? "HIT" : "MISS";
#endif

    if (NULL == http->storeEntry()) {
        /** \li If no StoreEntry object is current assume this object isn't in the cache set MISS*/
        debugs(85, 3, "clientProcessRequest2: StoreEntry is NULL -  MISS");
        http->logType = LOG_TCP_MISS;
        doGetMoreData();
        return;
    }

    if (Config.onoff.offline) {
        /** \li If we are running in offline mode set to HIT */
        debugs(85, 3, "clientProcessRequest2: offline HIT");
        http->logType = LOG_TCP_HIT;
        doGetMoreData();
        return;
    }

    if (http->redirect.status) {
        /** \li If redirection status is True force this to be a MISS */
        debugs(85, 3, HERE << "REDIRECT status forced StoreEntry to NULL (no body on 3XX responses)");
        http->storeEntry(NULL);
        http->logType = LOG_TCP_REDIRECT;
        doGetMoreData();
        return;
    }

    if (!e->validToSend()) {
        debugs(85, 3, "clientProcessRequest2: !storeEntryValidToSend MISS" );
        http->storeEntry(NULL);
        http->logType = LOG_TCP_MISS;
        doGetMoreData();
        return;
    }

    if (EBIT_TEST(e->flags, ENTRY_SPECIAL)) {
        /* \li Special entries are always hits, no matter what the client says */
        debugs(85, 3, "clientProcessRequest2: ENTRY_SPECIAL HIT");
        http->logType = LOG_TCP_HIT;
        doGetMoreData();
        return;
    }

    if (r->flags.noCache) {
        debugs(85, 3, "clientProcessRequest2: no-cache REFRESH MISS");
        http->storeEntry(NULL);
        http->logType = LOG_TCP_CLIENT_REFRESH_MISS;
        doGetMoreData();
        return;
    }

    debugs(85, 3, "clientProcessRequest2: default HIT");
    http->logType = LOG_TCP_HIT;
    doGetMoreData();
}