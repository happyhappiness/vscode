int64_t
Store::Disks::accumulateMore(const StoreEntry &entry) const
{
    const auto accumulated = entry.mem_obj->availableForSwapOut();

    /*
     * Keep accumulating more bytes until the set of disks eligible to accept
     * the entry becomes stable, and, hence, accumulating more is not going to
     * affect the cache_dir selection. A stable set is usually reached
     * immediately (or soon) because most configurations either do not use
     * cache_dirs with explicit min-size/max-size limits or use the same
     * max-size limit for all cache_dirs (and low min-size limits).
     */

    // Can the set of min-size cache_dirs accepting this entry change?
    if (accumulated < largestMinimumObjectSize)
        return largestMinimumObjectSize - accumulated;

    // Can the set of max-size cache_dirs accepting this entry change
    // (other than when the entry exceeds the largest maximum; see below)?
    if (accumulated <= secondLargestMaximumObjectSize)
        return secondLargestMaximumObjectSize - accumulated + 1;

    /*
     * Checking largestMaximumObjectSize instead eliminates the risk of starting
     * to swap out an entry that later grows too big, but also implies huge
     * accumulation in most environments. Accumulating huge entries not only
     * consumes lots of RAM but also creates a burst of doPages() write requests
     * that overwhelm the disk. To avoid these problems, we take the risk and
     * allow swap out now. The disk will quit swapping out if the entry
     * eventually grows too big for its selected cache_dir.
     */
    debugs(20, 3, "no: " << accumulated << '>' <<
           secondLargestMaximumObjectSize << ',' << largestMinimumObjectSize);
    return 0;
}