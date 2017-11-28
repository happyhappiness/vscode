void
HttpReply::updateOnNotModified(HttpReply const * freshRep)
{
    assert(freshRep);

    /* clean cache */
    hdrCacheClean();
    /* update raw headers */
    header.update(&freshRep->header,
                  (const HttpHeaderMask *) &Denied304HeadersMask);

    header.compact();
    /* init cache */
    hdrCacheInit();
}