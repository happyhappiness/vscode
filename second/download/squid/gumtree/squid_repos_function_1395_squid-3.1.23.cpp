void
StoreEntry::swapOutFileClose()
{
    assert(mem_obj != NULL);
    debugs(20, 3, "storeSwapOutFileClose: " << getMD5Text());
    debugs(20, 3, "storeSwapOutFileClose: sio = " << mem_obj->swapout.sio.getRaw());

    if (mem_obj->swapout.sio == NULL)
        return;

    storeClose(mem_obj->swapout.sio);
}