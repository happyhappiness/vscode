void
CossSwapDir::unlink(StoreEntry & e)
{
    debugs(79, 3, "storeCossUnlink: offset " << e.swap_filen);
    if (e.swap_status == SWAPOUT_DONE && EBIT_TEST(e.flags, ENTRY_VALIDATED)) {
        cur_size -= fs.blksize * sizeInBlocks(e.swap_file_sz);
        --n_disk_objects;
    }
    ++ StoreFScoss::GetInstance().stats.unlink.ops;
    ++ StoreFScoss::GetInstance().stats.unlink.success;
    storeCossRemove(this, &e);
}