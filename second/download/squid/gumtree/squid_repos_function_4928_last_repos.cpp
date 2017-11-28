void Rock::SwapDir::disconnect(StoreEntry &e)
{
    assert(e.swap_dirn == index);
    assert(e.swap_filen >= 0);
    // cannot have SWAPOUT_NONE entry with swap_filen >= 0
    assert(e.swap_status != SWAPOUT_NONE);

    // do not rely on e.swap_status here because there is an async delay
    // before it switches from SWAPOUT_WRITING to SWAPOUT_DONE.

    // since e has swap_filen, its slot is locked for reading and/or writing
    // but it is difficult to know whether THIS worker is reading or writing e,
    // especially since we may switch from writing to reading. This code relies
    // on Rock::IoState::writeableAnchor_ being set when we locked for writing.
    if (e.mem_obj && e.mem_obj->swapout.sio != NULL &&
            dynamic_cast<IoState&>(*e.mem_obj->swapout.sio).writeableAnchor_) {
        map->abortWriting(e.swap_filen);
        e.swap_dirn = -1;
        e.swap_filen = -1;
        e.swap_status = SWAPOUT_NONE;
        dynamic_cast<IoState&>(*e.mem_obj->swapout.sio).writeableAnchor_ = NULL;
        Store::Root().transientsAbandon(e); // broadcasts after the change
    } else {
        map->closeForReading(e.swap_filen);
        e.swap_dirn = -1;
        e.swap_filen = -1;
        e.swap_status = SWAPOUT_NONE;
    }
}