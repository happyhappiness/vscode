    flags.parsed_ok = 0;
    deferredparams.node = NULL;
    deferredparams.rep = NULL;
}

ClientSocketContext *
ClientSocketContextNew(ClientHttpRequest * http)
{
    ClientSocketContext *newContext;
    assert(http != NULL);
    newContext = new ClientSocketContext;
    newContext->http = http;
    return newContext;
}

#if USE_IDENT
static void
clientIdentDone(const char *ident, void *data)
{
    ConnStateData *conn = (ConnStateData *)data;
    xstrncpy(conn->rfc931, ident ? ident : dash_str, USER_IDENT_SZ);
}
#endif

void
clientUpdateStatCounters(log_type logType)
{
    statCounter.client_http.requests++;

    if (logTypeIsATcpHit(logType))
        statCounter.client_http.hits++;

    if (logType == LOG_TCP_HIT)
        statCounter.client_http.disk_hits++;
    else if (logType == LOG_TCP_MEM_HIT)
        statCounter.client_http.mem_hits++;
}

void
clientUpdateStatHistCounters(log_type logType, int svc_time)
{
    statHistCount(&statCounter.client_http.all_svc_time, svc_time);
    /**
     * The idea here is not to be complete, but to get service times
     * for only well-defined types.  For example, we don't include
     * LOG_TCP_REFRESH_FAIL because its not really a cache hit
     * (we *tried* to validate it, but failed).
     */

    switch (logType) {

    case LOG_TCP_REFRESH_UNMODIFIED:
        statHistCount(&statCounter.client_http.nh_svc_time, svc_time);
        break;

    case LOG_TCP_IMS_HIT:
        statHistCount(&statCounter.client_http.nm_svc_time, svc_time);
        break;

    case LOG_TCP_HIT:

    case LOG_TCP_MEM_HIT:

    case LOG_TCP_OFFLINE_HIT:
        statHistCount(&statCounter.client_http.hit_svc_time, svc_time);
        break;

    case LOG_TCP_MISS:

    case LOG_TCP_CLIENT_REFRESH_MISS:
        statHistCount(&statCounter.client_http.miss_svc_time, svc_time);
        break;

    default:
        /* make compiler warnings go away */
        break;
    }
