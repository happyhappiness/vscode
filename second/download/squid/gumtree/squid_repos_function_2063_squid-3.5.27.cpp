void
StoreController::memoryUnlink(StoreEntry &e)
{
    if (memStore)
        memStore->unlink(e);
    else // TODO: move into [non-shared] memory cache class when we have one
        e.destroyMemObject();
}