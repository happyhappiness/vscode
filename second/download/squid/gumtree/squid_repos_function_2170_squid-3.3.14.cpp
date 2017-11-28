static int
storeDigestResize(void)
{
    const int cap = storeDigestCalcCap();
    int diff;
    assert(store_digest);
    diff = abs(cap - store_digest->capacity);
    debugs(71, 2, "storeDigestResize: " <<
           store_digest->capacity << " -> " << cap << "; change: " <<
           diff << " (" << xpercentInt(diff, store_digest->capacity) << "%)" );
    /* avoid minor adjustments */

    if (diff <= store_digest->capacity / 10) {
        debugs(71, 2, "storeDigestResize: small change, will not resize.");
        return 0;
    } else {
        debugs(71, 2, "storeDigestResize: big change, resizing.");
        cacheDigestChangeCap(store_digest, cap);
        return 1;
    }
}