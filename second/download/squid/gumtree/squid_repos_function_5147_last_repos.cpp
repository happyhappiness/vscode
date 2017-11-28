void
Fs::Ufs::UFSSwapDir::unlink(StoreEntry & e)
{
    debugs(79, 3, HERE << "dirno " << index  << ", fileno "<<
           std::setfill('0') << std::hex << std::uppercase << std::setw(8) << e.swap_filen);
    if (e.swap_status == SWAPOUT_DONE) {
        cur_size -= fs.blksize * sizeInBlocks(e.swap_file_sz);
        --n_disk_objects;
    }
    replacementRemove(&e);
    mapBitReset(e.swap_filen);
    UFSSwapDir::unlinkFile(e.swap_filen);
    e.swap_filen = -1;
    e.swap_dirn = -1;
    e.swap_status = SWAPOUT_NONE;
}