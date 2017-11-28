void
clientUpdateHierCounters(HierarchyLogEntry * someEntry)
{
    ping_data *i;

    switch (someEntry->code) {
#if USE_CACHE_DIGESTS

    case CD_PARENT_HIT:

    case CD_SIBLING_HIT:
        ++ statCounter.cd.times_used;
        break;
#endif

    case SIBLING_HIT:

    case PARENT_HIT:

    case FIRST_PARENT_MISS:

    case CLOSEST_PARENT_MISS:
        ++ statCounter.icp.times_used;
        i = &someEntry->ping;

        if (clientPingHasFinished(i))
            statCounter.icp.querySvcTime.count(tvSubUsec(i->start, i->stop));

        if (i->timeout)
            ++ statCounter.icp.query_timeouts;

        break;

    case CLOSEST_PARENT:

    case CLOSEST_DIRECT:
        ++ statCounter.netdb.times_used;

        break;

    default:
        break;
    }
}