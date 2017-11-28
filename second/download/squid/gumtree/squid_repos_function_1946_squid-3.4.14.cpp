void
StoreController::reference(StoreEntry &e)
{
    // special entries do not belong to any specific Store, but are IN_MEMORY
    if (EBIT_TEST(e.flags, ENTRY_SPECIAL))
        return;

    /* Notify the fs that we're referencing this object again */

    if (e.swap_dirn > -1)
        swapDir->reference(e);

    // Notify the memory cache that we're referencing this object again
    if (memStore && e.mem_status == IN_MEMORY)
        memStore->reference(e);

    // TODO: move this code to a non-shared memory cache class when we have it
    if (e.mem_obj) {
        if (mem_policy->Referenced)
            mem_policy->Referenced(mem_policy, &e, &e.mem_obj->repl);
    }
}