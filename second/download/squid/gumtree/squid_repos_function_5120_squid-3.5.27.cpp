bool
Rock::SwapDir::anchorCollapsed(StoreEntry &collapsed, bool &inSync)
{
    if (!map || !theFile || !theFile->canRead())
        return false;

    sfileno filen;
    const Ipc::StoreMapAnchor *const slot = map->openForReading(
            reinterpret_cast<cache_key*>(collapsed.key), filen);
    if (!slot)
        return false;

    anchorEntry(collapsed, filen, *slot);
    inSync = updateCollapsedWith(collapsed, *slot);
    return true; // even if inSync is false
}