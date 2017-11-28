bool
MemStore::updateCollapsed(StoreEntry &collapsed)
{
    assert(collapsed.mem_obj);

    const sfileno index = collapsed.mem_obj->memCache.index;

    // already disconnected from the cache, no need to update
    if (index < 0)
        return true;

    if (!map)
        return false;

    const Ipc::StoreMapAnchor &anchor = map->readableEntry(index);
    return updateCollapsedWith(collapsed, index, anchor);
}