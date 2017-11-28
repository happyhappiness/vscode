Fs::Ufs::UFSSwapDir::swappedOut(const StoreEntry &e)
{
    cur_size += fs.blksize * sizeInBlocks(e.swap_file_sz);
    ++n_disk_objects;
}

void
Fs::Ufs::UFSSwapDir::logEntry(const StoreEntry & e, int op) const
{
    if (swaplog_fd < 0) {
        debugs(36, 5, "cannot log " << e << " in the middle of reconfiguration");
        return;
