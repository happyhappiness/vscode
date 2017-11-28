void
clientReplyContext::startError(ErrorState * err)
{
    createStoreEntry(http->request->method, RequestFlags());
    triggerInitialStoreRead();
    errorAppendEntry(http->storeEntry(), err);
}