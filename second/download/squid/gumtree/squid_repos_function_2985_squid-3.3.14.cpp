void
StoreEntry::getPublic (StoreClient *aClient, const char *uri, const HttpRequestMethod& method)
{
    assert (aClient);
    StoreEntry *result = storeGetPublic (uri, method);

    if (!result)
        result = NullStoreEntry::getInstance();

    aClient->created (result);
}