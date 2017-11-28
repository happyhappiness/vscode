void
StoreEntry::trimMemory(const bool preserveSwappable)
{
    /*
     * DPW 2007-05-09
     * Bug #1943.  We must not let go any data for IN_MEMORY
     * objects.  We have to wait until the mem_status changes.
     */
    if (mem_status == IN_MEMORY)
        return;

    if (EBIT_TEST(flags, ENTRY_SPECIAL))
        return; // cannot trim because we do not load them again

    if (!preserveSwappable) {
        if (mem_obj->policyLowestOffsetToKeep(0) == 0) {
            /* Nothing to do */
            return;
        }
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