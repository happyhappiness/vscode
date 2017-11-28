void
StoreController::sync(void)
{
    if (memStore)
        memStore->sync();
    swapDir->sync();
}