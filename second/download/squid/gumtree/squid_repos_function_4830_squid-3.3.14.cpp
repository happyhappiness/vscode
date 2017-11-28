bool
Rock::SwapDir::canStore(const StoreEntry &e, int64_t diskSpaceNeeded, int &load) const
{
    if (!::SwapDir::canStore(e, sizeof(DbCellHeader)+diskSpaceNeeded, load))
        return false;

    if (!theFile || !theFile->canWrite())
        return false;

    if (!map)
        return false;

    // Do not start I/O transaction if there are less than 10% free pages left.
    // TODO: reserve page instead
    if (needsDiskStrand() &&
            Ipc::Mem::PageLevel(Ipc::Mem::PageId::ioPage) >= 0.9 * Ipc::Mem::PageLimit(Ipc::Mem::PageId::ioPage)) {
        debugs(47, 5, HERE << "too few shared pages for IPC I/O left");
        return false;
    }

    if (io->shedLoad())
        return false;

    load = io->load();
    return true;
}