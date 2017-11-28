static void
storeSwapInFileNotify(void *data, int errflag, StoreIOState::Pointer self)
{
    store_client *sc = (store_client *)data;
    StoreEntry *e = sc->entry;

    debugs(1, 3, "storeSwapInFileNotify: changing " << e->swap_filen << "/" <<
           e->swap_dirn << " to " << sc->swapin_sio->swap_filen << "/" <<
           sc->swapin_sio->swap_dirn);

    e->swap_filen = sc->swapin_sio->swap_filen;
    e->swap_dirn = sc->swapin_sio->swap_dirn;
}