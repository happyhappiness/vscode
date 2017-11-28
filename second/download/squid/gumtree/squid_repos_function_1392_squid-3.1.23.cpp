static void
storeSwapOutFileNotify(void *data, int errflag, StoreIOState::Pointer self)
{
    generic_cbdata *c = (generic_cbdata *)data;
    StoreEntry *e = (StoreEntry *)c->data;
    MemObject *mem = e->mem_obj;
    assert(e->swap_status == SWAPOUT_WRITING);
    assert(mem);
    assert(mem->swapout.sio == self);
    assert(errflag == 0);
    e->swap_filen = mem->swapout.sio->swap_filen;
    e->swap_dirn = mem->swapout.sio->swap_dirn;
}