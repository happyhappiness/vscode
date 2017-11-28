StoreEntry *
storeCreateEntry(const char *url, const char *logUrl, const RequestFlags &flags, const HttpRequestMethod& method)
{
    StoreEntry *e = storeCreatePureEntry(url, logUrl, flags, method);
    e->lock("storeCreateEntry");

    if (neighbors_do_private_keys || !flags.hierarchical)
        e->setPrivateKey(false);
    else
        e->setPublicKey();

    return e;
}