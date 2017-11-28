bool
StoreController::anchorCollapsed(StoreEntry &collapsed, bool &inSync)
{
    // this method is designed to work with collapsed transients only
    assert(collapsed.mem_obj);
    assert(collapsed.mem_obj->xitTable.index >= 0);
    assert(collapsed.mem_obj->smpCollapsed);

    debugs(20, 7, "anchoring " << collapsed);

    bool found = false;
    if (memStore)
        found = memStore->anchorCollapsed(collapsed, inSync);
    if (!found && Config.cacheSwap.n_configured)
        found = anchorCollapsedOnDisk(collapsed, inSync);

    if (found) {
        if (inSync)
            debugs(20, 7, "anchored " << collapsed);
        else
            debugs(20, 5, "failed to anchor " << collapsed);
    } else {
        debugs(20, 7, "skipping not yet cached " << collapsed);
    }

    return found;
}