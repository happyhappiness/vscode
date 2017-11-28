void

storeRebuildComplete(struct _store_rebuild_data *dc)
{
    double dt;
    counts.objcount += dc->objcount;
    counts.expcount += dc->expcount;
    counts.scancount += dc->scancount;
    counts.clashcount += dc->clashcount;
    counts.dupcount += dc->dupcount;
    counts.cancelcount += dc->cancelcount;
    counts.invalid += dc->invalid;
    counts.badflags += dc->badflags;
    counts.bad_log_op += dc->bad_log_op;
    counts.zero_object_sz += dc->zero_object_sz;
    /*
     * When store_dirs_rebuilding == 1, it means we are done reading
     * or scanning all cache_dirs.  Now report the stats and start
     * the validation (storeCleanup()) thread.
     */

    if (StoreController::store_dirs_rebuilding > 1)
        return;

    dt = tvSubDsec(rebuild_start, current_time);

    debugs(20, 1, "Finished rebuilding storage from disk.");
    debugs(20, 1, "  " << std::setw(7) << counts.scancount  << " Entries scanned");
    debugs(20, 1, "  " << std::setw(7) << counts.invalid  << " Invalid entries.");
    debugs(20, 1, "  " << std::setw(7) << counts.badflags  << " With invalid flags.");
    debugs(20, 1, "  " << std::setw(7) << counts.objcount  << " Objects loaded.");
    debugs(20, 1, "  " << std::setw(7) << counts.expcount  << " Objects expired.");
    debugs(20, 1, "  " << std::setw(7) << counts.cancelcount  << " Objects cancelled.");
    debugs(20, 1, "  " << std::setw(7) << counts.dupcount  << " Duplicate URLs purged.");
    debugs(20, 1, "  " << std::setw(7) << counts.clashcount  << " Swapfile clashes avoided.");
    debugs(20, 1, "  Took "<< std::setw(3)<< std::setprecision(2) << dt << " seconds ("<< std::setw(6) <<
           ((double) counts.objcount / (dt > 0.0 ? dt : 1.0)) << " objects/sec).");
    debugs(20, 1, "Beginning Validation Procedure");

    eventAdd("storeCleanup", storeCleanup, NULL, 0.0, 1);

    xfree(RebuildProgress);

    RebuildProgress = NULL;
}