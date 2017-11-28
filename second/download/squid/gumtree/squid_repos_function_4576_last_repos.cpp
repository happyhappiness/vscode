void
Store::Controller::unlink(StoreEntry &e)
{
    memoryUnlink(e);
    if (swapDir && e.swap_filen >= 0)
        swapDir->unlink(e);
}