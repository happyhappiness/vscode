bool
Store::Controller::dereferenceIdle(StoreEntry &e, bool wantsLocalMemory)
{
    // special entries do not belong to any specific Store, but are IN_MEMORY
    if (EBIT_TEST(e.flags, ENTRY_SPECIAL))
        return true;

    bool keepInStoreTable = false; // keep only if somebody needs it there

    /* Notify the fs that we're not referencing this object any more */

    if (e.swap_filen > -1)
        keepInStoreTable = swapDir->dereference(e) || keepInStoreTable;

    // Notify the memory cache that we're not referencing this object any more
    if (memStore && e.mem_status == IN_MEMORY)
        keepInStoreTable = memStore->dereference(e) || keepInStoreTable;

    // TODO: move this code to a non-shared memory cache class when we have it
    if (e.mem_obj) {
        if (mem_policy->Dereferenced)
            mem_policy->Dereferenced(mem_policy, &e, &e.mem_obj->repl);
        // non-shared memory cache relies on store_table
        if (!memStore)
            keepInStoreTable = wantsLocalMemory || keepInStoreTable;
    }

    return keepInStoreTable;
}