int
storeDirWriteCleanLogs(int reopen)
{
    const StoreEntry *e = NULL;
    int n = 0;

    struct timeval start;
    double dt;
    RefCount<SwapDir> sd;
    int dirn;
    int notdone = 1;

    if (StoreController::store_dirs_rebuilding) {
        debugs(20, DBG_IMPORTANT, "Not currently OK to rewrite swap log.");
        debugs(20, DBG_IMPORTANT, "storeDirWriteCleanLogs: Operation aborted.");
        return 0;
    }

    debugs(20, DBG_IMPORTANT, "storeDirWriteCleanLogs: Starting...");
    getCurrentTime();
    start = current_time;

    for (dirn = 0; dirn < Config.cacheSwap.n_configured; ++dirn) {
        sd = dynamic_cast<SwapDir *>(INDEXSD(dirn));

        if (sd->writeCleanStart() < 0) {
            debugs(20, DBG_IMPORTANT, "log.clean.start() failed for dir #" << sd->index);
            continue;
        }
    }

    /*
     * This may look inefficient as CPU wise it is more efficient to do this
     * sequentially, but I/O wise the parallellism helps as it allows more
     * hdd spindles to be active.
     */
    while (notdone) {
        notdone = 0;

        for (dirn = 0; dirn < Config.cacheSwap.n_configured; ++dirn) {
            sd = dynamic_cast<SwapDir *>(INDEXSD(dirn));

            if (NULL == sd->cleanLog)
                continue;

            e = sd->cleanLog->nextEntry();

            if (!e)
                continue;

            notdone = 1;

            if (!sd->canLog(*e))
                continue;

            sd->cleanLog->write(*e);

            if ((++n & 0xFFFF) == 0) {
                getCurrentTime();
                debugs(20, DBG_IMPORTANT, "  " << std::setw(7) << n  <<
                       " entries written so far.");
            }
        }
    }

    /* Flush */
    for (dirn = 0; dirn < Config.cacheSwap.n_configured; ++dirn)
        dynamic_cast<SwapDir *>(INDEXSD(dirn))->writeCleanDone();

    if (reopen)
        storeDirOpenSwapLogs();

    getCurrentTime();

    dt = tvSubDsec(start, current_time);

    debugs(20, DBG_IMPORTANT, "  Finished.  Wrote " << n << " entries.");
    debugs(20, DBG_IMPORTANT, "  Took "<< std::setw(3)<< std::setprecision(2) << dt <<
           " seconds ("<< std::setw(6) << ((double) n / (dt > 0.0 ? dt : 1.0)) << " entries/sec).");

    return n;
}