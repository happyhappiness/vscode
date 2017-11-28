StoreEntry *
storeGetPublicByRequest(HttpRequest * req, const KeyScope keyScope)
{
    StoreEntry *e = storeGetPublicByRequestMethod(req, req->method, keyScope);

    if (e == NULL && req->method == Http::METHOD_HEAD)
        /* We can generate a HEAD reply from a cached GET object */
        e = storeGetPublicByRequestMethod(req, Http::METHOD_GET, keyScope);

    return e;
}