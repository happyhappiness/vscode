void
StoreEntry::trimMemory()
{
    /*
     * DPW 2007-05-09
     * Bug #1943.  We must not let go any data for IN_MEMORY
     * objects.  We have to wait until the mem_status changes.
     */
    if (mem_status == IN_MEMORY)
        return;

    if (mem_obj->policyLowestOffsetToKeep() == 0)
        /* Nothing to do */
        return;

    if (!swapOutAble()) {
        /*
         * Its not swap-able, and we're about to delete a chunk,
         * so we must make it PRIVATE.  This is tricky/ugly because
         * for the most part, we treat swapable == cachable here.
         */
        releaseRequest();
        mem_obj->trimUnSwappable ();
    } else {
        mem_obj->trimSwappable ();
    }
}