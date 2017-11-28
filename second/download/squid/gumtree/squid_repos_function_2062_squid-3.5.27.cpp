void
StoreController::memoryOut(StoreEntry &e, const bool preserveSwappable)
{
    bool keepInLocalMemory = false;
    if (memStore)
        memStore->write(e); // leave keepInLocalMemory false
    else
        keepInLocalMemory = keepForLocalMemoryCache(e);

    debugs(20, 7, HERE << "keepInLocalMemory: " << keepInLocalMemory);

    if (!keepInLocalMemory)
        e.trimMemory(preserveSwappable);
}