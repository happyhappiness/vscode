int
storeClientCopyPending(store_client * sc, StoreEntry * e, void *data)
{
#if STORE_CLIENT_LIST_DEBUG
    assert(sc == storeClientListSearch(e->mem_obj, data));
#endif
#ifndef SILLY_CODE

    assert(sc);
#endif

    assert(sc->entry == e);
#if SILLY_CODE

    if (sc == NULL)
        return 0;

#endif

    if (!sc->_callback.pending())
        return 0;

    return 1;
}