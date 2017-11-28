void
clientReplyContext::removeClientStoreReference(store_client **scp, ClientHttpRequest *aHttpRequest)
{
    StoreEntry *reference = aHttpRequest->storeEntry();
    removeStoreReference(scp, &reference);
    aHttpRequest->storeEntry(reference);
}