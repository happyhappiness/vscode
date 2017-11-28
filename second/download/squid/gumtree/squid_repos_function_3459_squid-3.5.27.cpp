void
clientReplyContext::saveState()
{
    assert(old_sc == NULL);
    debugs(88, 3, "clientReplyContext::saveState: saving store context");
    old_entry = http->storeEntry();
    old_sc = sc;
    old_lastmod = http->request->lastmod;
    old_etag = http->request->etag;
    old_reqsize = reqsize;
    tempBuffer.offset = reqofs;
    /* Prevent accessing the now saved entries */
    http->storeEntry(NULL);
    sc = NULL;
    reqsize = 0;
    reqofs = 0;
}