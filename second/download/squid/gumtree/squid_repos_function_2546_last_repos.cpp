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

    if (preserveSwappable)
        mem_obj->trimSwappable();
    else
        mem_obj->trimUnSwappable();

    debugs(88, 7, *this << " inmem_lo=" << mem_obj->inmem_lo);
}