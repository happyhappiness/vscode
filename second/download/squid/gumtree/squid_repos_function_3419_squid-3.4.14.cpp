void
clientReplyContext::cacheHit(StoreIOBuffer result)
{
    /** Ignore if the HIT object is being deleted. */
    if (deleting)
        return;

    StoreEntry *e = http->storeEntry();

    HttpRequest *r = http->request;

    debugs(88, 3, "clientCacheHit: " << http->uri << ", " << result.length << " bytes");

    if (http->storeEntry() == NULL) {
        debugs(88, 3, "clientCacheHit: request aborted");
        return;
    } else if (result.flags.error) {
        /* swap in failure */
        debugs(88, 3, "clientCacheHit: swapin failure for " << http->uri);
        http->logType = LOG_TCP_SWAPFAIL_MISS;
        removeClientStoreReference(&sc, http);
        processMiss();
        return;
    }

    if (result.length == 0) {
        /* the store couldn't get enough data from the file for us to id the
         * object
         */
        /* treat as a miss */
        http->logType = LOG_TCP_MISS;
        processMiss();
        return;
    }

    assert(!EBIT_TEST(e->flags, ENTRY_ABORTED));
    /* update size of the request */
    reqsize = result.length + reqofs;

    /*
     * Got the headers, now grok them
     */
    assert(http->logType == LOG_TCP_HIT);

    if (strcmp(e->mem_obj->url, http->request->storeId()) != 0) {
        debugs(33, DBG_IMPORTANT, "clientProcessHit: URL mismatch, '" << e->mem_obj->url << "' != '" << http->request->storeId() << "'");
        http->logType = LOG_TCP_MISS; // we lack a more precise LOG_*_MISS code
        processMiss();
        return;
    }

    switch (varyEvaluateMatch(e, r)) {

    case VARY_NONE:
        /* No variance detected. Continue as normal */
        break;

    case VARY_MATCH:
        /* This is the correct entity for this request. Continue */
        debugs(88, 2, "clientProcessHit: Vary MATCH!");
        break;

    case VARY_OTHER:
        /* This is not the correct entity for this request. We need
         * to requery the cache.
         */
        removeClientStoreReference(&sc, http);
        e = NULL;
        /* Note: varyEvalyateMatch updates the request with vary information
         * so we only get here once. (it also takes care of cancelling loops)
         */
        debugs(88, 2, "clientProcessHit: Vary detected!");
        clientGetMoreData(ourNode, http);
        return;

    case VARY_CANCEL:
        /* varyEvaluateMatch found a object loop. Process as miss */
        debugs(88, DBG_IMPORTANT, "clientProcessHit: Vary object loop!");
        http->logType = LOG_TCP_MISS; // we lack a more precise LOG_*_MISS code
        processMiss();
        return;
    }

    if (r->method == Http::METHOD_PURGE) {
        removeClientStoreReference(&sc, http);
        e = NULL;
        purgeRequest();
        return;
    }

    if (e->checkNegativeHit()
            && !r->flags.noCacheHack()
       ) {
        http->logType = LOG_TCP_NEGATIVE_HIT;
        sendMoreData(result);
    } else if (!http->flags.internal && refreshCheckHTTP(e, r)) {
        debugs(88, 5, "clientCacheHit: in refreshCheck() block");
        /*
         * We hold a stale copy; it needs to be validated
         */
        /*
         * The 'needValidation' flag is used to prevent forwarding
         * loops between siblings.  If our copy of the object is stale,
         * then we should probably only use parents for the validation
         * request.  Otherwise two siblings could generate a loop if
         * both have a stale version of the object.
         */
        r->flags.needValidation = true;

        if (e->lastmod < 0) {
            debugs(88, 3, "validate HIT object? NO. Missing Last-Modified header. Do MISS.");
            /*
             * Previous reply didn't have a Last-Modified header,
             * we cannot revalidate it.
             */
            http->logType = LOG_TCP_MISS;
            processMiss();
        } else if (r->flags.noCache) {
            debugs(88, 3, "validate HIT object? NO. Client sent CC:no-cache. Do CLIENT_REFRESH_MISS");
            /*
             * This did not match a refresh pattern that overrides no-cache
             * we should honour the client no-cache header.
             */
            http->logType = LOG_TCP_CLIENT_REFRESH_MISS;
            processMiss();
        } else if (r->protocol == AnyP::PROTO_HTTP) {
            debugs(88, 3, "validate HIT object? YES.");
            /*
             * Object needs to be revalidated
             * XXX This could apply to FTP as well, if Last-Modified is known.
             */
            processExpired();
        } else {
            debugs(88, 3, "validate HIT object? NO. Client protocol non-HTTP. Do MISS.");
            /*
             * We don't know how to re-validate other protocols. Handle
             * them as if the object has expired.
             */
            http->logType = LOG_TCP_MISS;
            processMiss();
        }
    } else if (r->conditional())
        processConditional(result);
    else {
        /*
         * plain ol' cache hit
         */

#if USE_DELAY_POOLS
        if (e->store_status != STORE_OK)
            http->logType = LOG_TCP_MISS;
        else
#endif
            if (e->mem_status == IN_MEMORY)
                http->logType = LOG_TCP_MEM_HIT;
            else if (Config.onoff.offline)
                http->logType = LOG_TCP_OFFLINE_HIT;

        sendMoreData(result);
    }
}