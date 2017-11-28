void
clientUpdateStatCounters(const LogTags &logType)
{
    ++statCounter.client_http.requests;

    if (logType.isTcpHit())
        ++statCounter.client_http.hits;

    if (logType.oldType == LOG_TCP_HIT)
        ++statCounter.client_http.disk_hits;
    else if (logType.oldType == LOG_TCP_MEM_HIT)
        ++statCounter.client_http.mem_hits;
}