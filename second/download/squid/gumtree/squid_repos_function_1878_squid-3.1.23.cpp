void
StoreController::reference(StoreEntry &e)
{
    /* Notify the fs that we're referencing this object again */

    if (e.swap_dirn > -1)
        e.store()->reference(e);

    /* Notify the memory cache that we're referencing this object again */
    if (e.mem_obj) {
        if (mem_policy->Referenced)
            mem_policy->Referenced(mem_policy, &e, &e.mem_obj->repl);
    }
}