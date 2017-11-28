bool
MemStore::anchorCollapsed(StoreEntry &collapsed, bool &inSync)
{
    if (!map)
        return false;

    sfileno index;
    const Ipc::StoreMapAnchor *const slot = map->openForReading(
            reinterpret_cast<cache_key*>(collapsed.key), index);
    if (!slot)
        return false;

    anchorEntry(collapsed, index, *slot);
    inSync = updateCollapsedWith(collapsed, index, *slot);
    return true; // even if inSync is false
}