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
    /* Prevent accessed the old saved entries */
    old_entry = NULL;
    old_sc = NULL;
    old_reqsize = 0;
    tempBuffer.offset = 0;
}