void
Store::Controller::maintain()
{
    static time_t last_warn_time = 0;

    PROF_start(storeMaintainSwapSpace);
    swapDir->maintain();

    /* this should be emitted by the oversize dir, not globally */

    if (Root().currentSize() > Store::Root().maxSize()) {
        if (squid_curtime - last_warn_time > 10) {
            debugs(20, DBG_CRITICAL, "WARNING: Disk space over limit: "
                   << Store::Root().currentSize() / 1024.0 << " KB > "
                   << (Store::Root().maxSize() >> 10) << " KB");
            last_warn_time = squid_curtime;
        }
    }

    PROF_stop(storeMaintainSwapSpace);
}