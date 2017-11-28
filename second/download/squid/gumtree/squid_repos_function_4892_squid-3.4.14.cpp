void Rock::SwapDir::disconnect(StoreEntry &e)
{
    assert(e.swap_dirn == index);
    assert(e.swap_filen >= 0);
    // cannot have SWAPOUT_NONE entry with swap_filen >= 0
    assert(e.swap_status != SWAPOUT_NONE);

    // do not rely on e.swap_status here because there is an async delay
    // before it switches from SWAPOUT_WRITING to SWAPOUT_DONE.

    // since e has swap_filen, its slot is locked for either reading or writing
    map->abortIo(e.swap_filen);
    e.swap_dirn = -1;
    e.swap_filen = -1;
    e.swap_status = SWAPOUT_NONE;
}