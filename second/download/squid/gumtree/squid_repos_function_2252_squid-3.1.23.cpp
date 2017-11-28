int
storeClientIsThisAClient(store_client * sc, void *someClient)
{
    return sc->owner == someClient;
}