bool
CossSwapDir::canStore(const StoreEntry &e, int64_t diskSpaceNeeded, int &load) const
{
    if (!SwapDir::canStore(e, diskSpaceNeeded, load))
        return false;

    load = io->load();
    return true;
}