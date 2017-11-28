static void
storeSwapOutFileNotify(void *data, int errflag, StoreIOState::Pointer self)
{
    StoreEntry *e;
    static_cast<generic_cbdata *>(data)->unwrap(&e);

    MemObject *mem = e->mem_obj;
    assert(e->swap_status == SWAPOUT_WRITING);
    assert(mem);
    assert(mem->swapout.sio == self);
    assert(errflag == 0);
    assert(e->swap_filen < 0); // if this fails, call SwapDir::disconnect(e)
    e->swap_filen = mem->swapout.sio->swap_filen;
    e->swap_dirn = mem->swapout.sio->swap_dirn;
}