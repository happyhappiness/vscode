void
StoreController::maybeTrimMemory(StoreEntry &e, const bool preserveSwappable)
{
    bool keepInLocalMemory = false;
    if (memStore)
        keepInLocalMemory = memStore->keepInLocalMemory(e);
    else
        keepInLocalMemory = keepForLocalMemoryCache(e);

    debugs(20, 7, HERE << "keepInLocalMemory: " << keepInLocalMemory);

    if (!keepInLocalMemory)
        e.trimMemory(preserveSwappable);
}