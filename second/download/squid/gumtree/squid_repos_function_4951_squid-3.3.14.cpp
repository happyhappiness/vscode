void
Fs::Ufs::UFSSwapDir::undoAddDiskRestore(StoreEntry *e)
{
    debugs(47, 5, HERE << *e);
    replacementRemove(e); // checks swap_dirn so do it before we invalidate it
    // Do not unlink the file as it might be used by a subsequent entry.
    mapBitReset(e->swap_filen);
    e->swap_filen = -1;
    e->swap_dirn = -1;
    cur_size -= fs.blksize * sizeInBlocks(e->swap_file_sz);
    --n_disk_objects;
}