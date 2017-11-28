static int
storeClientNoMoreToSend(StoreEntry * e, store_client * sc)
{
    int64_t len;

    if (e->store_status == STORE_PENDING)
        return 0;

    if ((len = e->objectLen()) < 0)
        return 0;

    if (sc->copyInto.offset < len)
        return 0;

    return 1;
}