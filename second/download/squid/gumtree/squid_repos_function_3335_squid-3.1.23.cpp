void
clientReplyContext::purgeDoPurgeGet(StoreEntry *newEntry)
{
    assert (newEntry);
    /* Move to new() when that is created */
    purgeStatus = HTTP_NOT_FOUND;

    if (!newEntry->isNull()) {
        /* Release the cached URI */
        debugs(88, 4, "clientPurgeRequest: GET '" << newEntry->url() << "'" );
#if USE_HTCP
        neighborsHtcpClear(newEntry, NULL, http->request, HttpRequestMethod(METHOD_GET), HTCP_CLR_PURGE);
#endif
        newEntry->release();
        purgeStatus = HTTP_OK;
    }

    lookingforstore = 4;
    StoreEntry::getPublicByRequestMethod(this, http->request, METHOD_HEAD);
}