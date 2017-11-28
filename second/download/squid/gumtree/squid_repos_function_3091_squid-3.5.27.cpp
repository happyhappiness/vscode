void
StoreEntry::setMemStatus(mem_status_t new_status)
{
    if (new_status == mem_status)
        return;

    // are we using a shared memory cache?
    if (Config.memShared && IamWorkerProcess()) {
        // This method was designed to update replacement policy, not to
        // actually purge something from the memory cache (TODO: rename?).
        // Shared memory cache does not have a policy that needs updates.
        mem_status = new_status;
        return;
    }

    assert(mem_obj != NULL);

    if (new_status == IN_MEMORY) {
        assert(mem_obj->inmem_lo == 0);

        if (EBIT_TEST(flags, ENTRY_SPECIAL)) {
            debugs(20, 4, "not inserting special " << *this << " into policy");
        } else {
            mem_policy->Add(mem_policy, this, &mem_obj->repl);
            debugs(20, 4, "inserted " << *this << " key: " << getMD5Text());
        }

        ++hot_obj_count; // TODO: maintain for the shared hot cache as well
    } else {
        if (EBIT_TEST(flags, ENTRY_SPECIAL)) {
            debugs(20, 4, "not removing special " << *this << " from policy");
        } else {
            mem_policy->Remove(mem_policy, this, &mem_obj->repl);
            debugs(20, 4, "removed " << *this);
        }

        --hot_obj_count;
    }

    mem_status = new_status;
}