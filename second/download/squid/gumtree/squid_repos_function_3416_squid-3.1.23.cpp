void
ClientHttpRequest::updateCounters()
{
    clientUpdateStatCounters(logType);

    if (request->errType != ERR_NONE)
        statCounter.client_http.errors++;

    clientUpdateStatHistCounters(logType,
                                 tvSubMsec(start_time, current_time));

    clientUpdateHierCounters(&request->hier);
}