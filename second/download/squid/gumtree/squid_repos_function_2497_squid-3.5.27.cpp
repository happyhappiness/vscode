bool
store_client::startSwapin()
{
    debugs(90, 3, "store_client::doCopy: Need to open swap in file");
    /* gotta open the swapin file */

    if (storeTooManyDiskFilesOpen()) {
        /* yuck -- this causes a TCP_SWAPFAIL_MISS on the client side */
        fail();
        flags.store_copying = false;
        return false;
    } else if (!flags.disk_io_pending) {
        /* Don't set store_io_pending here */
        storeSwapInStart(this);

        if (swapin_sio == NULL) {
            fail();
            flags.store_copying = false;
            return false;
        }

        return true;
    } else {
        debugs(90, DBG_IMPORTANT, "WARNING: Averted multiple fd operation (1)");
        flags.store_copying = false;
        return false;
    }
}