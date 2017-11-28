void
StoreController::maintain()
{
    static time_t last_warn_time = 0;

    PROF_start(storeMaintainSwapSpace);
    swapDir->maintain();

    /* this should be emitted by the oversize dir, not globally */

    if (store_swap_size > Store::Root().maxSize()) {
        if (squid_curtime - last_warn_time > 10) {
            debugs(20, 0, "WARNING: Disk space over limit: " << store_swap_size << " KB > "
                   << Store::Root().maxSize() << " KB");
            last_warn_time = squid_curtime;
        }
    }

    PROF_stop(storeMaintainSwapSpace);
}