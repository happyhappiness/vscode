bool
Fs::Ufs::UFSSwapDir::canStore(const StoreEntry &e, int64_t diskSpaceNeeded, int &load) const
{
    if (!SwapDir::canStore(e, diskSpaceNeeded, load))
        return false;

    if (IO->shedLoad())
        return false;

    load = IO->load();
    return true;
}