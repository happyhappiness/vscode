void
SignalEngine::doShutdown(time_t wait)
{
    debugs(1, 1, "Preparing for shutdown after " << statCounter.client_http.requests << " requests");
    debugs(1, 1, "Waiting " << wait << " seconds for active connections to finish");

    shutting_down = 1;

#if USE_WIN32_SERVICE
    WIN32_svcstatusupdate(SERVICE_STOP_PENDING, (wait + 1) * 1000);
#endif

    serverConnectionsClose();
    eventAdd("SquidShutdown", &StopEventLoop, this, (double) (wait + 1), 1, false);
}