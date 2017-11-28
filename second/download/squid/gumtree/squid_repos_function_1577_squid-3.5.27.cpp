void
SignalEngine::doShutdown(time_t wait)
{
    debugs(1, DBG_IMPORTANT, "Preparing for shutdown after " << statCounter.client_http.requests << " requests");
    debugs(1, DBG_IMPORTANT, "Waiting " << wait << " seconds for active connections to finish");

    shutting_down = 1;

#if USE_WIN32_SERVICE
    WIN32_svcstatusupdate(SERVICE_STOP_PENDING, (wait + 1) * 1000);
#endif

    /* run the closure code which can be shared with reconfigure */
    serverConnectionsClose();
    RunRegisteredHere(RegisteredRunner::startShutdown);
    eventAdd("SquidShutdown", &FinalShutdownRunners, this, (double) (wait + 1), 1, false);
}