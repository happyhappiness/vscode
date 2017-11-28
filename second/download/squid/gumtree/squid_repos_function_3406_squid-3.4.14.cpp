void
clientReplyContext::removeStoreReference(store_client ** scp,
        StoreEntry ** ep)
{
    StoreEntry *e;
    store_client *sc_tmp = *scp;

    if ((e = *ep) != NULL) {
        *ep = NULL;
        storeUnregister(sc_tmp, e, this);
        *scp = NULL;
        e->unlock();
    }
}