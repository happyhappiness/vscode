void
clientReplyContext::sendNotModified()
{
    StoreEntry *e = http->storeEntry();
    const time_t timestamp = e->timestamp;
    HttpReply *const temprep = e->getReply()->make304();
    http->logType = LOG_TCP_IMS_HIT;
    removeClientStoreReference(&sc, http);
    createStoreEntry(http->request->method, request_flags());
    e = http->storeEntry();
    // Copy timestamp from the original entry so the 304
    // reply has a meaningful Age: header.
    e->timestamp = timestamp;
    e->replaceHttpReply(temprep);
    e->complete();
    /*
     * TODO: why put this in the store and then serialise it and
     * then parse it again. Simply mark the request complete in
     * our context and write the reply struct to the client side.
     */
    triggerInitialStoreRead();
}