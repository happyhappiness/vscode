void
store_client::scheduleDiskRead()
{
    /* What the client wants is not in memory. Schedule a disk read */
    if (getType() == STORE_DISK_CLIENT) {
        // we should have called startSwapin() already
        assert(swapin_sio != NULL);
    } else if (!swapin_sio && !startSwapin()) {
        debugs(90, 3, "bailing after swapin start failure for " << *entry);
        assert(!flags.store_copying);
        return;
    }

    assert(!flags.disk_io_pending);

    debugs(90, 3, "reading " << *entry << " from disk");

    fileRead();

    flags.store_copying = false;
}