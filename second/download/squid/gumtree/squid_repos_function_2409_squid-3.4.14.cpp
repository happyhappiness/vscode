void
store_client::scheduleDiskRead()
{
    /* What the client wants is not in memory. Schedule a disk read */
    assert(STORE_DISK_CLIENT == getType());

    assert(!flags.disk_io_pending);

    debugs(90, 3, "store_client::doCopy: reading from STORE");

    fileRead();

    flags.store_copying = false;
}