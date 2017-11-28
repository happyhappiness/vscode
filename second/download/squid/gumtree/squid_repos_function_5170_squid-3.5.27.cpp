void
Rock::SwapDir::markForUnlink(StoreEntry &e)
{
    debugs(47, 5, e);
    map->freeEntry(e.swap_filen);
}