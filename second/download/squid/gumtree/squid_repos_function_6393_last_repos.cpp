void
DiskDaemonDiskIOModule::init()
{
    /* We may be reused - for instance in coss - eventually.
     * When we do, we either need per-using-module stats (
     * no singleton pattern), or we need to refcount the
     * initialisation level and handle multiple clients.
     * RBC - 20030718.
     */
    assert(!initialised);
    memset(&diskd_stats, '\0', sizeof(diskd_stats));
#if 0
    /*
     * DPW 2007-04-12
     * No debugging here please because this method is called before
     * the debug log is configured and we'll get the message on
     * stderr when doing things like 'squid -k reconfigure'
     */
    debugs(47, DBG_IMPORTANT, "diskd started");
#endif
    initialised = true;

    registerWithCacheManager();
}