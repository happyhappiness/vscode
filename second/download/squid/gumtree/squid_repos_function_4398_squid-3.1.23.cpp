static void
asStateFree(void *data)
{
    ASState *asState = (ASState *)data;
    debugs(53, 3, "asnStateFree: " << asState->entry->url()  );
    storeUnregister(asState->sc, asState->entry, asState);
    asState->entry->unlock();
    HTTPMSGUNLOCK(asState->request);
    cbdataFree(asState);
}