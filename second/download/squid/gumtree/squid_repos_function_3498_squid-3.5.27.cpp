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
    if (r->flags.noCache || r->flags.noCacheHack())
        ipcacheInvalidateNegative(r->GetHost());

#if USE_CACHE_DIGESTS
    lookup_type = http->storeEntry() ? "HIT" : "MISS";
#endif

    if (NULL == http->storeEntry()) {
        /** \li If no StoreEntry object is current assume this object isn't in the cache set MISS*/
        debugs(85, 3, "StoreEntry is NULL -  MISS");
        http->logType = LOG_TCP_MISS;
        doGetMoreData();
        return;
    }

    if (Config.onoff.offline) {
        /** \li If we are running in offline mode set to HIT */
        debugs(85, 3, "offline HIT " << *e);
        http->logType = LOG_TCP_HIT;
        doGetMoreData();
        return;
    }

    if (http->redirect.status) {
        /** \li If redirection status is True force this to be a MISS */
        debugs(85, 3, "REDIRECT status forced StoreEntry to NULL (no body on 3XX responses) " << *e);
        forgetHit();
        http->logType = LOG_TCP_REDIRECT;
        doGetMoreData();
        return;
    }

    if (!e->validToSend()) {
        debugs(85, 3, "!storeEntryValidToSend MISS " << *e);
        forgetHit();
        http->logType = LOG_TCP_MISS;
        doGetMoreData();
        return;
    }

    if (EBIT_TEST(e->flags, ENTRY_SPECIAL)) {
        /* \li Special entries are always hits, no matter what the client says */
        debugs(85, 3, "ENTRY_SPECIAL HIT " << *e);
        http->logType = LOG_TCP_HIT;
        doGetMoreData();
        return;
    }

    if (r->flags.noCache) {
        debugs(85, 3, "no-cache REFRESH MISS " << *e);
        forgetHit();
        http->logType = LOG_TCP_CLIENT_REFRESH_MISS;
        doGetMoreData();
        return;
    }

    debugs(85, 3, "default HIT " << *e);
    http->logType = LOG_TCP_HIT;
    doGetMoreData();
}