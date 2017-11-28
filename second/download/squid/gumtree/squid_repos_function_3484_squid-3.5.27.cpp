void
clientReplyContext::purgeDoPurgeGet(StoreEntry *newEntry)
{
    assert (newEntry);
    /* Move to new() when that is created */
    purgeStatus = Http::scNotFound;

    if (!newEntry->isNull()) {
        /* Release the cached URI */
        debugs(88, 4, "clientPurgeRequest: GET '" << newEntry->url() << "'" );
#if USE_HTCP
        neighborsHtcpClear(newEntry, NULL, http->request, HttpRequestMethod(Http::METHOD_GET), HTCP_CLR_PURGE);
#endif
        newEntry->release();
        purgeStatus = Http::scOkay;
    }

    lookingforstore = 4;
    StoreEntry::getPublicByRequestMethod(this, http->request, Http::METHOD_HEAD);
}