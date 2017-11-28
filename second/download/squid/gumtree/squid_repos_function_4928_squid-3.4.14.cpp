void
Rock::SwapDir::unlink(StoreEntry &e)
{
    debugs(47, 5, HERE << e);
    ignoreReferences(e);
    map->free(e.swap_filen);
    disconnect(e);
}