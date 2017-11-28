StoreEntry *
storeGetPublicByRequest(HttpRequest * req)
{
    StoreEntry *e = storeGetPublicByRequestMethod(req, req->method);

    if (e == NULL && req->method == METHOD_HEAD)
        /* We can generate a HEAD reply from a cached GET object */
        e = storeGetPublicByRequestMethod(req, METHOD_GET);

    return e;
}