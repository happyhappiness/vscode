void
clientReplyContext::purgeFoundObject(StoreEntry *entry)
{
    assert (entry && !entry->isNull());

    if (EBIT_TEST(entry->flags, ENTRY_SPECIAL)) {
        http->logType = LOG_TCP_DENIED;
        ErrorState *err = clientBuildError(ERR_ACCESS_DENIED, HTTP_FORBIDDEN, NULL,
                                           http->getConn()->clientConnection->remote, http->request);
        startError(err);
        return;
    }

    StoreIOBuffer localTempBuffer;
    /* Swap in the metadata */
    http->storeEntry(entry);

    http->storeEntry()->lock();
    http->storeEntry()->createMemObject(http->uri, http->log_uri);

    http->storeEntry()->mem_obj->method = http->request->method;

    sc = storeClientListAdd(http->storeEntry(), this);

    http->logType = LOG_TCP_HIT;

    reqofs = 0;

    localTempBuffer.offset = http->out.offset;

    localTempBuffer.length = next()->readBuffer.length;

    localTempBuffer.data = next()->readBuffer.data;

    storeClientCopy(sc, http->storeEntry(),
                    localTempBuffer, CacheHit, this);
}