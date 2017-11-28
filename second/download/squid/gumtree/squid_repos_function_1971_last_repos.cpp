static void
storeClientCopyEvent(void *data)
{
    store_client *sc = (store_client *)data;
    debugs(90, 3, "storeClientCopyEvent: Running");
    assert (sc->flags.copy_event_pending);
    sc->flags.copy_event_pending = false;

    if (!sc->_callback.pending())
        return;

    storeClientCopy2(sc->entry, sc);
}