StoreEntry *
storeGetPublicByRequestMethod(HttpRequest * req, const HttpRequestMethod& method)
{
    return Store::Root().get(storeKeyPublicByRequestMethod(req, method));
}