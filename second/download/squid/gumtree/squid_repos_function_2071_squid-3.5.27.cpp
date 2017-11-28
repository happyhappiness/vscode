void
StoreController::syncCollapsed(const sfileno xitIndex)
{
    assert(transients);

    StoreEntry *collapsed = transients->findCollapsed(xitIndex);
    if (!collapsed) { // the entry is no longer locally active, ignore update
        debugs(20, 7, "not SMP-syncing not-transient " << xitIndex);
        return;
    }
    assert(collapsed->mem_obj);
    assert(collapsed->mem_obj->smpCollapsed);

    debugs(20, 7, "syncing " << *collapsed);

    bool abandoned = transients->abandoned(*collapsed);
    bool found = false;
    bool inSync = false;
    if (memStore && collapsed->mem_obj->memCache.io == MemObject::ioDone) {
        found = true;
        inSync = true;
        debugs(20, 7, "fully mem-loaded " << *collapsed);
    } else if (memStore && collapsed->mem_obj->memCache.index >= 0) {
        found = true;
        inSync = memStore->updateCollapsed(*collapsed);
    } else if (collapsed->swap_filen >= 0) {
        found = true;
        inSync = collapsed->store()->updateCollapsed(*collapsed);
    } else {
        found = anchorCollapsed(*collapsed, inSync);
    }

    if (abandoned && collapsed->store_status == STORE_PENDING) {
        debugs(20, 3, "aborting abandoned but STORE_PENDING " << *collapsed);
        collapsed->abort();
        return;
    }

    if (inSync) {
        debugs(20, 5, "synced " << *collapsed);
        collapsed->invokeHandlers();
    } else if (found) { // unrecoverable problem syncing this entry
        debugs(20, 3, "aborting unsyncable " << *collapsed);
        collapsed->abort();
    } else { // the entry is still not in one of the caches
        debugs(20, 7, "waiting " << *collapsed);
    }
}