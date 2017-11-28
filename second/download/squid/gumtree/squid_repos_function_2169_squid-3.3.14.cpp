static int
storeDigestCalcCap(void)
{
    /*
     * To-Do: Bloom proved that the optimal filter utilization is 50% (half of
     * the bits are off). However, we do not have a formula to calculate the
     * number of _entries_ we want to pre-allocate for.
     */
    const int hi_cap = Store::Root().maxSize() / Config.Store.avgObjectSize;
    const int lo_cap = 1 + Store::Root().currentSize() / Config.Store.avgObjectSize;
    const int e_count = StoreEntry::inUseCount();
    int cap = e_count ? e_count :hi_cap;
    debugs(71, 2, "storeDigestCalcCap: have: " << e_count << ", want " << cap <<
           " entries; limits: [" << lo_cap << ", " << hi_cap << "]");

    if (cap < lo_cap)
        cap = lo_cap;

    /* do not enforce hi_cap limit, average-based estimation may be wrong
     *if (cap > hi_cap)
     *  cap = hi_cap;
     */
    return cap;
}