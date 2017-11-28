void
StoreController::dereference(StoreEntry & e)
{
    /* Notify the fs that we're not referencing this object any more */

    if (e.swap_filen > -1)
        e.store()->dereference(e);

    /* Notify the memory cache that we're not referencing this object any more */
    if (e.mem_obj) {
        if (mem_policy->Dereferenced)
            mem_policy->Dereferenced(mem_policy, &e, &e.mem_obj->repl);
    }
}