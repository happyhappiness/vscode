bool
refreshIsCachable(const StoreEntry * entry)
{
    /*
     * Don't look at the request to avoid no-cache and other nuisances.
     * the object should have a mem_obj so the URL will be found there.
     * minimum_expiry_time seconds delta (defaults to 60 seconds), to
     * avoid objects which expire almost immediately, and which can't
     * be refreshed.
     */
    int reason = refreshCheck(entry, NULL, Config.minimum_expiry_time);
    ++ refreshCounts[rcStore].total;
    ++ refreshCounts[rcStore].status[reason];

    if (reason < STALE_MUST_REVALIDATE)
        /* Does not need refresh. This is certainly cachable */
        return true;

    if (entry->lastModified() < 0)
        /* We should know entry's modification time to do a refresh */
        return false;

    if (entry->mem_obj == NULL)
        /* no mem_obj? */
        return true;

    if (entry->getReply() == NULL)
        /* no reply? */
        return true;

    if (entry->getReply()->content_length == 0)
        /* No use refreshing (caching?) 0 byte objects */
        return false;

    /* This seems to be refreshable. Cache it */
    return true;
}