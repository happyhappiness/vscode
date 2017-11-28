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
        sc->flags.copy_event_pending = true;
        debugs(90, 3, "storeClientCopy2: Queueing storeClientCopyEvent()");
        eventAdd("storeClientCopyEvent", storeClientCopyEvent, sc, 0.0, 0);
        return;
    }

    debugs(90, 3, "storeClientCopy2: " << e->getMD5Text());
    assert(sc->_callback.pending());
    /*
     * We used to check for ENTRY_ABORTED here.  But there were some
     * problems.  For example, we might have a slow client (or two) and
     * the peer server is reading far ahead and swapping to disk.  Even
     * if the peer aborts, we want to give the client(s)
     * everything we got before the abort condition occurred.
     */
    /* Warning: doCopy may indirectly free itself in callbacks,
     * hence the lock to keep it active for the duration of
     * this function
     * XXX: Locking does not prevent calling sc destructor (it only prevents
     * freeing sc memory) so sc may become invalid from C++ p.o.v.
     */
    CbcPointer<store_client> tmpLock = sc;
    assert (!sc->flags.store_copying);
    sc->doCopy(e);
    assert(!sc->flags.store_copying);
}