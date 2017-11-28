void
DiskThreadsIOStrategy::sync()
{
    if (!initialised)
        return;			/* nothing to do then */

    /* Flush all pending operations */
    debugs(32, 2, "aioSync: flushing pending I/O operations");

    do {
        callback();
    } while (squidaio_sync());

    debugs(32, 2, "aioSync: done");
}