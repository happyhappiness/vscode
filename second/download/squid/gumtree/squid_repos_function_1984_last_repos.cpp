static void
storeClientReadHeader(void *data, const char *buf, ssize_t len, StoreIOState::Pointer)
{
    store_client *sc = (store_client *)data;
    sc->readHeader(buf, len);
}