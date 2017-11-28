static void
storeClientCopy2(StoreEntry * e, store_client * sc)
{
    /* reentrancy not allowed  - note this could lead to
     * dropped events
     */

    if (sc->flags.copy_event_pending) {
        return;
    }

    if (EBIT_TEST(e->flags, ENTRY_FWD_HDR_WAIT)) {
        debugs(90, 5, "storeClientCopy2: returning because ENTRY_FWD_HDR_WAIT set");
        return;
    }

    if (sc->flags.store_copying) {
        sc->flags.copy_event_pending = 1;
        debugs(90, 3, "storeClientCopy2: Queueing storeClientCopyEvent()");
        eventAdd("storeClientCopyEvent", storeClientCopyEvent, sc, 0.0, 0);
        return;
    }

    debugs(90, 3, "storeClientCopy2: " << e->getMD5Text());
    assert(sc->_callback.pending());
    /*
     * We used to check for ENTRY_ABORTED here.  But there were some
     * problems.  For example, we might have a slow client (or two) and
     * the server-side is reading far ahead and swapping to disk.  Even
     * if the server-side aborts, we want to give the client(s)
     * everything we got before the abort condition occurred.
     */
    /* Warning: doCopy may indirectly free itself in callbacks,
     * hence the lock to keep it active for the duration of
     * this function
     */
    cbdataInternalLock(sc);
    assert (sc->flags.store_copying == 0);
    sc->doCopy(e);
    assert (sc->flags.store_copying == 0);
    cbdataInternalUnlock(sc);
}