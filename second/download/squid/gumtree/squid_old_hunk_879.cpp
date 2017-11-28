void
StoreController::get(String const key, STOREGETCLIENT aCallback, void *aCallbackData)
{
    fatal("not implemented");
}

// move this into [non-shared] memory cache class when we have one
/// whether e should be kept in local RAM for possible future caching
bool
StoreController::keepForLocalMemoryCache(const StoreEntry &e) const
{
    if (!e.memoryCachable())
        return false;

    // does the current and expected size obey memory caching limits?
    assert(e.mem_obj);
