void
Rock::SwapDir::writeError(StoreEntry &e)
{
    // Do not abortWriting here. The entry should keep the write lock
    // instead of losing association with the store and confusing core.
    map->freeEntry(e.swap_filen); // will mark as unusable, just in case

    Store::Root().transientsAbandon(e);

    // All callers must also call IoState callback, to propagate the error.
}