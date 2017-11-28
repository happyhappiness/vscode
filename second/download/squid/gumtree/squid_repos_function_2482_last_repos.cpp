StoreEntry *
storeGetPublicByRequestMethod(HttpRequest * req, const HttpRequestMethod& method, const KeyScope keyScope)
{
    return Store::Root().get(storeKeyPublicByRequestMethod(req, method, keyScope));
}