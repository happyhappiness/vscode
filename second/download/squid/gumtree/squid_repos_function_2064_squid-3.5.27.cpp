void
StoreController::memoryDisconnect(StoreEntry &e)
{
    if (memStore)
        memStore->disconnect(e);
    // else nothing to do for non-shared memory cache
}