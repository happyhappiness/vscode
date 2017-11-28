bool
HttpReply::updateOnNotModified(HttpReply const * freshRep)
{
    assert(freshRep);

    /* update raw headers */
    if (!header.update(&freshRep->header))
        return false;

    /* clean cache */
    hdrCacheClean();

    header.compact();
    /* init cache */
    hdrCacheInit();

    return true;
}