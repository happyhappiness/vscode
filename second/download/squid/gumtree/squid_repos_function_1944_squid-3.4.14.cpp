void
allocate_new_swapdir(SquidConfig::_cacheSwap * swap)
{
    if (swap->swapDirs == NULL) {
        swap->n_allocated = 4;
        swap->swapDirs = static_cast<SwapDir::Pointer *>(xcalloc(swap->n_allocated, sizeof(SwapDir::Pointer)));
    }

    if (swap->n_allocated == swap->n_configured) {
        swap->n_allocated <<= 1;
        SwapDir::Pointer *const tmp = static_cast<SwapDir::Pointer *>(xcalloc(swap->n_allocated, sizeof(SwapDir::Pointer)));
        memcpy(tmp, swap->swapDirs, swap->n_configured * sizeof(SwapDir *));
        xfree(swap->swapDirs);
        swap->swapDirs = tmp;
    }
}