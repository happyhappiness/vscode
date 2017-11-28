void
MemObject::trimSwappable()
{
    int64_t new_mem_lo = policyLowestOffsetToKeep();
    /*
     * We should only free up to what we know has been written
     * to disk, not what has been queued for writing.  Otherwise
     * there will be a chunk of the data which is not in memory
     * and is not yet on disk.
     * The -1 makes sure the page isn't freed until storeSwapOut has
     * walked to the next page. (mem->swapout.memnode)
     */
    int64_t on_disk;

    if ((on_disk = objectBytesOnDisk()) - 1 < new_mem_lo)
        new_mem_lo = on_disk - 1;

    if (new_mem_lo == -1)
        new_mem_lo = 0;	/* the above might become -1 */

    data_hdr.freeDataUpto(new_mem_lo);

    inmem_lo = new_mem_lo;
}