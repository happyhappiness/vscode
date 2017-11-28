void
StoreEntry::setMemStatus(mem_status_t new_status)
{
    if (new_status == mem_status)
        return;

    // are we using a shared memory cache?
    if (Config.memShared && IamWorkerProcess()) {
        // enumerate calling cases if shared memory is enabled
        assert(new_status != IN_MEMORY || EBIT_TEST(flags, ENTRY_SPECIAL));
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
            debugs(20, 4, "StoreEntry::setMemStatus: not inserting special " << mem_obj->url << " into policy");
        } else {
            mem_policy->Add(mem_policy, this, &mem_obj->repl);
            debugs(20, 4, "StoreEntry::setMemStatus: inserted mem node " << mem_obj->url << " key: " << getMD5Text());
        }

        ++hot_obj_count; // TODO: maintain for the shared hot cache as well
    } else {
        if (EBIT_TEST(flags, ENTRY_SPECIAL)) {
            debugs(20, 4, "StoreEntry::setMemStatus: special entry " << mem_obj->url);
        } else {
            mem_policy->Remove(mem_policy, this, &mem_obj->repl);
            debugs(20, 4, "StoreEntry::setMemStatus: removed mem node " << mem_obj->url);
        }

        --hot_obj_count;
    }

    mem_status = new_status;
}