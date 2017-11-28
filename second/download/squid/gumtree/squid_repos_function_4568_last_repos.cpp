void
Store::Controller::sync(void)
{
    if (memStore)
        memStore->sync();
    swapDir->sync();
}