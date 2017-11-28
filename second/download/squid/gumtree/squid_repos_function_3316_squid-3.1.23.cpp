void
clientReplyContext::processExpired()
{
    char *url = http->uri;
    StoreEntry *entry = NULL;
    debugs(88, 3, "clientReplyContext::processExpired: '" << http->uri << "'");
    assert(http->storeEntry()->lastmod >= 0);
    /*
     * check if we are allowed to contact other servers
     * @?@: Instead of a 504 (Gateway Timeout) reply, we may want to return
     *      a stale entry *if* it matches client requirements
     */

    if (http->onlyIfCached()) {
        processOnlyIfCachedMiss();
        return;
    }

    http->request->flags.refresh = 1;
#if STORE_CLIENT_LIST_DEBUG
    /* Prevent a race with the store client memory free routines
     */
    assert(storeClientIsThisAClient(sc, this));
#endif
    /* Prepare to make a new temporary request */
    saveState();
    entry = storeCreateEntry(url,
                             http->log_uri, http->request->flags, http->request->method);
    /* NOTE, don't call StoreEntry->lock(), storeCreateEntry() does it */
    sc = storeClientListAdd(entry, this);
#if DELAY_POOLS
    /* delay_id is already set on original store client */
    sc->setDelayId(DelayId::DelayClient(http));
#endif

    http->request->lastmod = old_entry->lastmod;
    debugs(88, 5, "clientReplyContext::processExpired : lastmod " << entry->lastmod );
    http->storeEntry(entry);
    assert(http->out.offset == 0);

    /*
     * A refcounted pointer so that FwdState stays around as long as
     * this clientReplyContext does
     */
    FwdState::fwdStart(http->getConn() != NULL ? http->getConn()->fd : -1,
                       http->storeEntry(),
                       http->request);
    /* Register with storage manager to receive updates when data comes in. */

    if (EBIT_TEST(entry->flags, ENTRY_ABORTED))
        debugs(88, 0, "clientReplyContext::processExpired: Found ENTRY_ABORTED object");

    {
        /* start counting the length from 0 */
        StoreIOBuffer localTempBuffer(HTTP_REQBUF_SZ, 0, tempbuf);
        storeClientCopy(sc, entry, localTempBuffer, HandleIMSReply, this);
    }
}