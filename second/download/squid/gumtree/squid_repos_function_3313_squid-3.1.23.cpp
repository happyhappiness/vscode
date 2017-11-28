void
clientReplyContext::startError(ErrorState * err)
{
    createStoreEntry(http->request->method, request_flags());
    triggerInitialStoreRead();
    errorAppendEntry(http->storeEntry(), err);
}