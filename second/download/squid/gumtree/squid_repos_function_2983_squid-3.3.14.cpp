void
StoreEntry::getPublicByRequestMethod  (StoreClient *aClient, HttpRequest * request, const HttpRequestMethod& method)
{
    assert (aClient);
    StoreEntry *result = storeGetPublicByRequestMethod( request, method);

    if (!result)
        aClient->created (NullStoreEntry::getInstance());
    else
        aClient->created (result);
}