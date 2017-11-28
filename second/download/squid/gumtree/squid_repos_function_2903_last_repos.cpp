void
clientReplyContext::triggerInitialStoreRead()
{
    /* when confident, 0 becomes reqofs, and then this factors into
     * startSendProcess
     */
    assert(reqofs == 0);
    StoreIOBuffer localTempBuffer (next()->readBuffer.length, 0, next()->readBuffer.data);
    storeClientCopy(sc, http->storeEntry(), localTempBuffer, SendMoreData, this);
}