SwapDir::Pointer
StoreEntry::store() const
{
    assert(0 <= swap_dirn && swap_dirn < Config.cacheSwap.n_configured);
    return INDEXSD(swap_dirn);
}