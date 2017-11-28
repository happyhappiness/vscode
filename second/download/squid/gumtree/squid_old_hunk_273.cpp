 * i.e. e->referenced()
 * so that the entry can notify the creating Store
 */
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

StoreEntry *

StoreController::get
(const cache_key *key)
{

    return swapDir->get
           (key);
}

void

StoreController::get
(String const key, STOREGETCLIENT aCallback, void *aCallbackData)
{
    fatal("not implemented");
}

StoreHashIndex::StoreHashIndex()
{
    if (store_table)
        abort();
