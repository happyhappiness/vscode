void
StoreEntry::getPublicByRequest (StoreClient *aClient, HttpRequest * request)
{
    assert (aClient);
    StoreEntry *result = storeGetPublicByRequest (request);

    if (!result)
        result = NullStoreEntry::getInstance();

    aClient->created (result);
}