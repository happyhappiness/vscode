void
StoreEntry::delayAwareRead(int fd, char *buf, int len, AsyncCall::Pointer callback)
{
    size_t amountToRead = bytesWanted(Range<size_t>(0, len));
    /* sketch: readdeferer* = getdeferer.
     * ->deferRead (fd, buf, len, callback, DelayAwareRead, this)
     */

    if (amountToRead == 0) {
        assert (mem_obj);
        /* read ahead limit */
        /* Perhaps these two calls should both live in MemObject */
#if DELAY_POOLS

        if (!mem_obj->readAheadPolicyCanRead()) {
#endif
            mem_obj->delayRead(DeferredRead(DeferReader, this, CommRead(fd, buf, len, callback)));
            return;
#if DELAY_POOLS

        }

        /* delay id limit */
        mem_obj->mostBytesAllowed().delayRead(DeferredRead(DeferReader, this, CommRead(fd, buf, len, callback)));

        return;

#endif

    }

    comm_read(fd, buf, amountToRead, callback);
}