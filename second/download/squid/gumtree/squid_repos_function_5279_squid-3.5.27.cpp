void
Fs::Ufs::UFSSwapDir::maintain()
{
    /* TODO: possible options for improvement;
     *
     * Note that too much aggression here is not good. It means that disk
     * controller is getting a long queue of removals to act on, along
     * with its regular I/O queue, and that client traffic is 'paused'
     * and growing the network I/O queue as well while the scan happens.
     * Possibly bad knock-on effects as Squid catches up on all that.
     *
     * Bug 2448 may have been a sign of what can wrong. At the least it
     * provides a test case for aggression effects in overflow conditions.
     *
     * - base removal limit on space saved, instead of count ?
     *
     * - base removal rate on a traffic speed counter ?
     *   as the purge took up more time out of the second it would grow to
     *   a graceful full pause
     *
     * - pass out a value to cause another event to be scheduled immediately
     *   instead of waiting a whole second more ?
     *   knock on; schedule less if all caches are under low-water
     *
     * - admin configurable removal rate or count ?
     *   the current numbers are arbitrary, config helps with experimental
     *   trials and future-proofing the install base.
     *   we also have this indirectly by shifting the relative positions
     *   of low-, high- water and the total capacity limit.
     */

    // minSize() is swap_low_watermark in bytes
    const uint64_t lowWaterSz = minSize();

    if (currentSize() < lowWaterSz) {
        debugs(47, 5, "space still available in " << path);
        return;
    }

    /* We can't delete objects while rebuilding swap */
    /* XXX each store should start maintaining as it comes online. */
    if (StoreController::store_dirs_rebuilding) {
        // suppress the warnings, except once each minute
        static int64_t lastWarn = 0;
        int warnLevel = 3;
        if (lastWarn+60 < squid_curtime) {
            lastWarn = squid_curtime;
            warnLevel = DBG_IMPORTANT;
        }
        debugs(47, warnLevel, StoreController::store_dirs_rebuilding << " cache_dir still rebuilding. Skip GC for " << path);
        return;
    }

    // maxSize() is cache_dir total size in bytes
    const uint64_t highWaterSz = ((maxSize() * Config.Swap.highWaterMark) / 100);

    // f is percentage of 'gap' filled between low- and high-water.
    // Used to reduced purge rate when between water markers, and
    // to multiply it more agressively the further above high-water
    // it reaches. But in a graceful linear growth curve.
    double f = 1.0;
    if (highWaterSz > lowWaterSz) {
        // might be equal. n/0 is bad.
        f = (double) (currentSize() - lowWaterSz) / (highWaterSz - lowWaterSz);
    }

    // how deep to look for a single object that can be removed
    int max_scan = (int) (f * 400.0 + 100.0);

    // try to purge only this many objects this cycle.
    int max_remove = (int) (f * 300.0 + 20.0);

    /*
     * This is kinda cheap, but so we need this priority hack?
     */
    debugs(47, 3, "f=" << f << ", max_scan=" << max_scan << ", max_remove=" << max_remove);

    RemovalPurgeWalker *walker = repl->PurgeInit(repl, max_scan);

    int removed = 0;
    // only purge while above low-water
    while (currentSize() >= lowWaterSz) {

        // stop if we reached max removals for this cycle,
        // Bug 2448 may be from this not clearing enough,
        // but it predates the current algorithm so not sure
        if (removed >= max_remove)
            break;

        StoreEntry *e = walker->Next(walker);

        // stop if all objects are locked / in-use,
        // or the cache is empty
        if (!e)
            break;      /* no more objects */

        ++removed;

        e->release();
    }

    walker->Done(walker);
    debugs(47, (removed ? 2 : 3), path <<
           " removed " << removed << "/" << max_remove << " f=" <<
           std::setprecision(4) << f << " max_scan=" << max_scan);

    // what if cache is still over the high watermark ?
    // Store::Maintain() schedules another purge in 1 second.
}