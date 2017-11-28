void
clientUpdateStatCounters(log_type logType)
{
    ++statCounter.client_http.requests;

    if (logTypeIsATcpHit(logType))
        ++statCounter.client_http.hits;

    if (logType == LOG_TCP_HIT)
        ++statCounter.client_http.disk_hits;
    else if (logType == LOG_TCP_MEM_HIT)
        ++statCounter.client_http.mem_hits;
}