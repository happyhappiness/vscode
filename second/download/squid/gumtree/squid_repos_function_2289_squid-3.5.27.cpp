static uint64_t
storeDigestCalcCap()
{
    /*
     * To-Do: Bloom proved that the optimal filter utilization is 50% (half of
     * the bits are off). However, we do not have a formula to calculate the
     * number of _entries_ we want to pre-allocate for.
     */
    const uint64_t hi_cap = Store::Root().maxSize() / Config.Store.avgObjectSize;
    const uint64_t lo_cap = 1 + Store::Root().currentSize() / Config.Store.avgObjectSize;
    const uint64_t e_count = StoreEntry::inUseCount();
    uint64_t cap = e_count ? e_count : hi_cap;
    debugs(71, 2, "have: " << e_count << ", want " << cap <<
           " entries; limits: [" << lo_cap << ", " << hi_cap << "]");

    if (cap < lo_cap)
        cap = lo_cap;

    /* do not enforce hi_cap limit, average-based estimation may be wrong
     *if (cap > hi_cap)
     *  cap = hi_cap;
     */

    // Bug 4534: we still have to set an upper-limit at some reasonable value though.
    // this matches cacheDigestCalcMaskSize doing (cap*bpe)+7 < INT_MAX
    const uint64_t absolute_max = (INT_MAX -8) / Config.digest.bits_per_entry;
    if (cap > absolute_max) {
        static time_t last_loud = 0;
        if (last_loud < squid_curtime - 86400) {
            debugs(71, DBG_IMPORTANT, "WARNING: Cache Digest cannot store " << cap << " entries. Limiting to " << absolute_max);
            last_loud = squid_curtime;
        } else {
            debugs(71, 3, "WARNING: Cache Digest cannot store " << cap << " entries. Limiting to " << absolute_max);
        }
        cap = absolute_max;
    }

    return cap;
}