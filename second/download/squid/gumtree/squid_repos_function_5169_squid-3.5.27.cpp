void
Rock::SwapDir::unlink(StoreEntry &e)
{
    debugs(47, 5, HERE << e);
    ignoreReferences(e);
    map->freeEntry(e.swap_filen);
    disconnect(e);
}