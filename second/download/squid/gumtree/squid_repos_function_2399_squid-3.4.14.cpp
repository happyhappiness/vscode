store_client *
storeClientListAdd(StoreEntry * e, void *data)
{
    MemObject *mem = e->mem_obj;
    store_client *sc;
    assert(mem);
#if STORE_CLIENT_LIST_DEBUG

    if (storeClientListSearch(mem, data) != NULL)
        /* XXX die! */
        assert(1 == 0);

#endif

    sc = new store_client (e);

    mem->addClient(sc);

    return sc;
}