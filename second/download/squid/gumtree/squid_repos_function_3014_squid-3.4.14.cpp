void
StoreEntry::delayAwareRead(const Comm::ConnectionPointer &conn, char *buf, int len, AsyncCall::Pointer callback)
{
    size_t amountToRead = bytesWanted(Range<size_t>(0, len));
    /* sketch: readdeferer* = getdeferer.
     * ->deferRead (fd, buf, len, callback, DelayAwareRead, this)
     */

    if (amountToRead == 0) {
        assert (mem_obj);
        /* read ahead limit */
        /* Perhaps these two calls should both live in MemObject */
#if USE_DELAY_POOLS
        if (!mem_obj->readAheadPolicyCanRead()) {
#endif
            mem_obj->delayRead(DeferredRead(DeferReader, this, CommRead(conn, buf, len, callback)));
            return;
#if USE_DELAY_POOLS
        }

        /* delay id limit */
        mem_obj->mostBytesAllowed().delayRead(DeferredRead(DeferReader, this, CommRead(conn, buf, len, callback)));
        return;

#endif

    }

    if (fd_table[conn->fd].closing()) {
        // Readers must have closing callbacks if they want to be notified. No
        // readers appeared to care around 2009/12/14 as they skipped reading
        // for other reasons. Closing may already be true at the delyaAwareRead
        // call time or may happen while we wait after delayRead() above.
        debugs(20, 3, HERE << "wont read from closing " << conn << " for " <<
               callback);
        return; // the read callback will never be called
    }

    comm_read(conn, buf, amountToRead, callback);
}