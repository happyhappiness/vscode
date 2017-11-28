static bool
storeDigestResize()
{
    const uint64_t cap = storeDigestCalcCap();
    assert(store_digest);
    uint64_t diff;
    if (cap > store_digest->capacity)
        diff = cap - store_digest->capacity;
    else
        diff = store_digest->capacity - cap;
    debugs(71, 2, store_digest->capacity << " -> " << cap << "; change: " <<
           diff << " (" << xpercentInt(diff, store_digest->capacity) << "%)" );
    /* avoid minor adjustments */

    if (diff <= store_digest->capacity / 10) {
        debugs(71, 2, "small change, will not resize.");
        return false;
    } else {
        debugs(71, 2, "big change, resizing.");
        cacheDigestChangeCap(store_digest, cap);
    }
    return true;
}