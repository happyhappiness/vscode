StoreEntry *
storeGetPublic(const char *uri, const HttpRequestMethod& method)
{
    return Store::Root().get(storeKeyPublic(uri, method));
}