void clientReplyContext::setReplyToStoreEntry(StoreEntry *entry, const char *reason)
{
    entry->lock(); // removeClientStoreReference() unlocks
    sc = storeClientListAdd(entry, this);
#if USE_DELAY_POOLS
    sc->setDelayId(DelayId::DelayClient(http));
#endif
    reqofs = 0;
    reqsize = 0;
    if (http->request)
        http->request->ignoreRange(reason);
    flags.storelogiccomplete = 1;
    http->storeEntry(entry);
}