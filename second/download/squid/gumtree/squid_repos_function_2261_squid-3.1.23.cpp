void
store_client::startSwapin()
{
    debugs(90, 3, "store_client::doCopy: Need to open swap in file");
    /* gotta open the swapin file */

    if (storeTooManyDiskFilesOpen()) {
        /* yuck -- this causes a TCP_SWAPFAIL_MISS on the client side */
        fail();
        flags.store_copying = 0;
        return;
    } else if (!flags.disk_io_pending) {
        /* Don't set store_io_pending here */
        storeSwapInStart(this);

        if (swapin_sio == NULL) {
            fail();
            flags.store_copying = 0;
            return;
        }

        /*
         * If the open succeeds we either copy from memory, or
         * schedule a disk read in the next block.
         */
        scheduleRead();

        return;
    } else {
        debugs(90, 1, "WARNING: Averted multiple fd operation (1)");
        flags.store_copying = 0;
        return;
    }
}