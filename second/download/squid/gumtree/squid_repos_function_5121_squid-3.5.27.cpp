bool
Rock::SwapDir::updateCollapsed(StoreEntry &collapsed)
{
    if (!map || !theFile || !theFile->canRead())
        return false;

    if (collapsed.swap_filen < 0) // no longer using a disk cache
        return true;
    assert(collapsed.swap_dirn == index);

    const Ipc::StoreMapAnchor &s = map->readableEntry(collapsed.swap_filen);
    return updateCollapsedWith(collapsed, s);
}