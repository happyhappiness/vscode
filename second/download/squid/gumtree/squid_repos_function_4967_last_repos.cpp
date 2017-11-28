void
Rock::SwapDir::writeError(StoreIOState &sio)
{
    // Do not abortWriting here. The entry should keep the write lock
    // instead of losing association with the store and confusing core.
    map->freeEntry(sio.swap_filen); // will mark as unusable, just in case

    if (sio.touchingStoreEntry())
        Store::Root().transientsAbandon(*sio.e);
    // else noop: a fresh entry update error does not affect stale entry readers

    // All callers must also call IoState callback, to propagate the error.
}