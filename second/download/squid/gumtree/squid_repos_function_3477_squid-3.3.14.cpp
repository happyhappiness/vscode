void
clientUpdateStatHistCounters(log_type logType, int svc_time)
{
    statCounter.client_http.allSvcTime.count(svc_time);
    /**
     * The idea here is not to be complete, but to get service times
     * for only well-defined types.  For example, we don't include
     * LOG_TCP_REFRESH_FAIL because its not really a cache hit
     * (we *tried* to validate it, but failed).
     */

    switch (logType) {

    case LOG_TCP_REFRESH_UNMODIFIED:
        statCounter.client_http.nearHitSvcTime.count(svc_time);
        break;

    case LOG_TCP_IMS_HIT:
        statCounter.client_http.nearMissSvcTime.count(svc_time);
        break;

    case LOG_TCP_HIT:

    case LOG_TCP_MEM_HIT:

    case LOG_TCP_OFFLINE_HIT:
        statCounter.client_http.hitSvcTime.count(svc_time);
        break;

    case LOG_TCP_MISS:

    case LOG_TCP_CLIENT_REFRESH_MISS:
        statCounter.client_http.missSvcTime.count(svc_time);
        break;

    default:
        /* make compiler warnings go away */
        break;
    }
}