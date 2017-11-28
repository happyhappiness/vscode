void
clientReplyContext::restoreState()
{
    assert(old_sc != NULL);
    debugs(88, 3, "clientReplyContext::restoreState: Restoring store context");
    removeClientStoreReference(&sc, http);
    http->storeEntry(old_entry);
    sc = old_sc;
    reqsize = old_reqsize;
    reqofs = tempBuffer.offset;
    http->request->lastmod = old_lastmod;
    http->request->etag = old_etag;
    /* Prevent accessed the old saved entries */
    old_entry = NULL;
    old_sc = NULL;
    old_lastmod = -1;
    old_etag.clean();
    old_reqsize = 0;
    tempBuffer.offset = 0;
}