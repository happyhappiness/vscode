int
ClientInfo::quotaForDequed()
{
    /* If we have multiple clients and give full bucketSize to each client then
     * clt1 may often get a lot more because clt1->clt2 time distance in the
     * select(2) callback order may be a lot smaller than cltN->clt1 distance.
     * We divide quota evenly to be more fair. */

    if (!rationedCount) {
        rationedCount = quotaQueue->size() + 1;

        // The delay in ration recalculation _temporary_ deprives clients from
        // bytes that should have trickled in while rationedCount was positive.
        refillBucket();

        // Rounding errors do not accumulate here, but we round down to avoid
        // negative bucket sizes after write with rationedCount=1.
        rationedQuota = static_cast<int>(floor(bucketSize/rationedCount));
        debugs(77,5, HERE << "new rationedQuota: " << rationedQuota <<
               '*' << rationedCount);
    }

    --rationedCount;
    debugs(77,7, HERE << "rationedQuota: " << rationedQuota <<
           " rations remaining: " << rationedCount);

    // update 'last seen' time to prevent clientdb GC from dropping us
    last_seen = squid_curtime;
    return rationedQuota;
}