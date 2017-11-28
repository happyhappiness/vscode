static void
storeGetMemSpace(int size)
{
    PROF_start(storeGetMemSpace);
    StoreEntry *e = NULL;
    int released = 0;
    static time_t last_check = 0;
    size_t pages_needed;
    RemovalPurgeWalker *walker;

    if (squid_curtime == last_check) {
        PROF_stop(storeGetMemSpace);
        return;
    }

    last_check = squid_curtime;

    pages_needed = (size / SM_PAGE_SIZE) + 1;

    if (mem_node::InUseCount() + pages_needed < store_pages_max) {
        PROF_stop(storeGetMemSpace);
        return;
    }

    debugs(20, 2, "storeGetMemSpace: Starting, need " << pages_needed <<
           " pages");

    /* XXX what to set as max_scan here? */
    walker = mem_policy->PurgeInit(mem_policy, 100000);

    while ((e = walker->Next(walker))) {
        e->purgeMem();
        released++;

        if (mem_node::InUseCount() + pages_needed < store_pages_max)
            break;
    }

    walker->Done(walker);
    debugs(20, 3, "storeGetMemSpace stats:");
    debugs(20, 3, "  " << std::setw(6) << hot_obj_count  << " HOT objects");
    debugs(20, 3, "  " << std::setw(6) << released  << " were released");
    PROF_stop(storeGetMemSpace);
}