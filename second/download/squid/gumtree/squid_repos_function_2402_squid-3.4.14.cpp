void
storeClientCopy(store_client * sc,
                StoreEntry * e,
                StoreIOBuffer copyInto,
                STCB * callback,
                void *data)
{
    assert (sc != NULL);
    sc->copy(e, copyInto,callback,data);
}