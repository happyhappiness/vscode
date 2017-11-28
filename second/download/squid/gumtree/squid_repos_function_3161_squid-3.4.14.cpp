static void
storeSwapInFileClosed(void *data, int errflag, StoreIOState::Pointer self)
{
    store_client *sc = (store_client *)data;
    debugs(20, 3, "storeSwapInFileClosed: sio=" << sc->swapin_sio.getRaw() << ", errflag=" << errflag);
    sc->swapin_sio = NULL;

    if (sc->_callback.pending()) {
        assert (errflag <= 0);
        sc->callback(0, errflag ? true : false);
    }

    ++statCounter.swap.ins;
}