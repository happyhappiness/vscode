void
Store::Controller::markForUnlink(StoreEntry &e)
{
    if (transients && e.mem_obj && e.mem_obj->xitTable.index >= 0)
        transients->markForUnlink(e);
    if (memStore && e.mem_obj && e.mem_obj->memCache.index >= 0)
        memStore->markForUnlink(e);
    if (swapDir && e.swap_filen >= 0)
        swapDir->markForUnlink(e);
}