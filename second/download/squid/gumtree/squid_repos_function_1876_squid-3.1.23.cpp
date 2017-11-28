void
allocate_new_swapdir(SquidConfig::_cacheSwap * swap)
{
    if (swap->swapDirs == NULL) {
        swap->n_allocated = 4;
        swap->swapDirs = static_cast<StorePointer *>(xcalloc(swap->n_allocated, sizeof(StorePointer)));
    }

    if (swap->n_allocated == swap->n_configured) {
        StorePointer *tmp;
        swap->n_allocated <<= 1;
        tmp = static_cast<StorePointer *>(xcalloc(swap->n_allocated, sizeof(StorePointer)));
        xmemcpy(tmp, swap->swapDirs, swap->n_configured * sizeof(SwapDir *));
        xfree(swap->swapDirs);
        swap->swapDirs = tmp;
    }
}