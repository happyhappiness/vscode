Store::Disk &
StoreEntry::disk() const
{
    assert(0 <= swap_dirn && swap_dirn < Config.cacheSwap.n_configured);
    const RefCount<Store::Disk> &sd = INDEXSD(swap_dirn);
    assert(sd);
    return *sd;
}